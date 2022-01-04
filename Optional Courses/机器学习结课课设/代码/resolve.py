import json
import os
import time
import pandas as pd
import numpy as np
from translate import translate
from langdetect import detect
import string
from nltk.corpus import stopwords
import nltk
import nltk.stem

base_path = "D:\\PyCharmproject\\NewsEmotionPrediction"

# 打开json文件
def open_file(file):
    f = open(file, encoding='utf-8')
    return f


# 从文档获得数据
def get_data(file):
    data = json.load(file)
    return data


# 语言检测
def is_en(content):
    try:
        return detect(content) == 'en'
    except Exception:
        return False


# 将数据翻译为英文
def translate_to_en(content):
    if is_en(content) is False:
        return translate(content)
    else:
        return content


# 训练集数据转至csv文件
def train_data_to_csv(dataset):
    for i in range(len(dataset)):
        time.sleep(1)
        content = dataset[i]['content']
        label = dataset[i]['label']
        if label is None or content is None:
            continue

        # 直接使用百度API时有些长难句会有一定问题，不知道怎么处理，所以这里遇到长难句直接跳过不进行处理，之后人工添加
        try:
            content = translate_to_en(content)
            list_item = [content, label]
            frame = pd.DataFrame([list_item], columns=['content', 'label'])
            to_csv_path = os.path.join(base_path, "dataset\\train.csv")
            frame.to_csv(to_csv_path, mode="a", index=False, header=False)
        except Exception:
            i = i + 1

        print(str(i) + " th data resolved.")

# 测试集数据转至csv文件
def test_data_to_csv(dataset):
    for i in range(len(dataset)):
        time.sleep(1)
        content = dataset[i]['content']
        if content is None:
            continue

        # 直接使用百度API时有些长难句会有一定问题，不知道怎么处理，所以这里遇到长难句直接跳过不进行处理，之后人工添加
        try:
            content = translate_to_en(content)
            list_item = [content]
            frame = pd.DataFrame([list_item], columns=['content'])
            to_csv_path = os.path.join(base_path, "dataset\\test.csv")
            frame.to_csv(to_csv_path, mode="a", index=False, header=False)
        except Exception:
            i = i + 1

        print(str(i) + " th data resolved.")

# 处理训练集
def resolve_train():
    print("Resolving train dataset.")
    file_path = os.path.join(base_path, "dataset\\train.json")
    f = open_file(file_path)
    data = np.array(get_data(f))
    train_data_to_csv(data)
    print("Resolving finish.")


# 处理测试集
def resolve_test():
    print("Resolving test dataset.")
    file_path = os.path.join(base_path, "dataset\\test.json")
    f = open_file(file_path)
    data = np.array(get_data(f))
    test_data_to_csv(data)
    print("Resolving finish.")


# 去除标点
def abort_punctuation(content):
    punctuations_list = str.maketrans('', '', string.punctuation)
    return content.translate(punctuations_list)


# 分词
def split_words(content):
    return nltk.word_tokenize(content)


# 去除停用词
def abort_stop_words(content):
    return [w for w in content if not w in stopwords.words('english')]


# 提取词干
def stemming(content):
    s = nltk.stem.SnowballStemmer('english')  # 参数：选择的语言
    return [s.stem(ws) for ws in content]


# 数据清理
def clean_train():
    frame = pd.read_csv(os.path.join(base_path, "dataset\\train.csv"), header=None)
    contents = frame[0]
    labels = frame[1]
    for i in range(len(contents)):
        print("Cleaning "+str(i)+" th data.")
        content = contents[i].lower()
        content = abort_punctuation(content)
        content = split_words(content)
        content = abort_stop_words(content)
        content = stemming(content)
        frame = pd.DataFrame([[content, labels[i]]], columns=['content', 'label'])
        to_csv_path = os.path.join(base_path, "dataset\\resolved_train.csv")
        frame.to_csv(to_csv_path, mode="a", index=False, header=False)


def clean_test():
    frame = pd.read_csv(os.path.join(base_path, "dataset\\test.csv"), header=None)
    contents = frame[0]

    for i in range(len(contents)):
        print("Cleaning " + str(i) + " th data.")
        content = contents[i].lower()
        content = abort_punctuation(content)
        content = split_words(content)
        content = abort_stop_words(content)
        content = stemming(content)
        frame = pd.DataFrame([[content]], columns=['content'])
        to_csv_path = os.path.join(base_path, "dataset\\resolved_test.csv")
        frame.to_csv(to_csv_path, mode="a", index=False, header=False)


if __name__ == '__main__':
    print("Resolving...")
    # 进行翻译
    resolve_train()
    resolve_test()

    print("Cleaning...")
    # 数据清洗
    clean_train()
    clean_test()

    print("End...")
