import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.neighbors import KNeighborsClassifier as kNN
from sklearn.svm import LinearSVC

if __name__ == '__main__':
    path = 'D:\\PyCharmproject\\NewsEmotionPrediction\\dataset\\'  # 数据集路径
    train = pd.read_csv(path + 'resolved_train.csv', header=None)  # 读取训练集
    test = pd.read_csv(path + 'resolved_test.csv', header=None)  # 读取测试集

    v = CountVectorizer()
    X_train = v.fit_transform(train[0])
    X_test = v.transform(test[0])

    tfidf = TfidfTransformer()
    X_train = tfidf.fit_transform(X_train)
    X_test = tfidf.transform(X_test)

    # 贝叶斯
    clf = MultinomialNB(alpha=0.01)
    clf.fit(X_train, train[1])
    pred = clf.predict(X_test)

    for i in pred:
        frame = pd.DataFrame([i], columns=['label'])
        to_csv_path = "D:\\PyCharmproject\\NewsEmotionPrediction\\dataset\\result_nb.csv"
        frame.to_csv(to_csv_path, mode="a", index=False, header=False)
    
    # KNN
    clf1 = kNN(4)
    clf1.fit(X_train, train[1])
    pred = clf1.predict(X_test)

    for i in pred:
        frame = pd.DataFrame([i], columns=['label'])
        to_csv_path = "D:\\PyCharmproject\\NewsEmotionPrediction\\dataset\\result_knn.csv"
        frame.to_csv(to_csv_path, mode="a", index=False, header=False)
    # SVM
    svc = LinearSVC(penalty='l2', loss='squared_hinge', dual=True, tol=0.0001, C=10, multi_class='crammer_singer',
                    fit_intercept=True, intercept_scaling=1, class_weight=None, verbose=0, random_state=None,
                    max_iter=10000)

    svc.fit(X_train, train[1])
    pred = svc.predict(X_test)

    for i in pred:
        frame = pd.DataFrame([i], columns=['label'])
        to_csv_path = "D:\\PyCharmproject\\NewsEmotionPrediction\\dataset\\result_svm.csv"
        frame.to_csv(to_csv_path, mode="a", index=False, header=False)
