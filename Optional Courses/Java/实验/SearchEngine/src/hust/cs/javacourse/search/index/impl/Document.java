package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.List;

/**
 *<pre>
 *     AbstractDocument是文档对象的抽象父类.
 *          文档对象是解析一个文本文件得到结果，文档对象里面包含：
 *              文档id.
 *              文档的绝对路径.
 *              文档包含的三元组对象列表，一个三元组对象是抽象类AbstractTermTuple的子类实例
 *</pre>
 */
public class Document extends AbstractDocument {
    /**
     * 无参构造
     */
    public Document(){}

    public Document(int docId, String docPath, List<AbstractTermTuple> tuples) {
        super(docId, docPath, tuples);
    }

    /**
     * 构造函数
     *
     * @param docId：文档id
     * @param docPath：文档绝对路径
     */
    public Document(int docId, String docPath) {
        super(docId, docPath);
    }

    /**
     * 获得文档id
     *
     * @return ：文档id
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 设置文档id
     *
     * @param docId：文档id
     */
    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    /**
     * 获得文档绝对路径
     *
     * @return ：文档绝对路径
     */
    @Override
    public String getDocPath() {
        return this.docPath;
    }

    /**
     * 设置文档绝对路径
     *
     * @param docPath：文档绝对路径
     */
    @Override
    public void setDocPath(String docPath) {
        this.docPath = docPath;
    }

    /**
     * 获得文档包含的三元组列表
     *
     * @return ：文档包含的三元组列表
     */
    @Override
    public List<AbstractTermTuple> getTuples() {
        return this.tuples;
    }

    /**
     * 向文档对象里添加三元组, 要求不能有内容重复的三元组
     *
     * @param tuple ：待添加的三元组
     */
    @Override
    public void addTuple(AbstractTermTuple tuple) {
        if (!contains(tuple)) {
            this.tuples.add(tuple);
        }
    }

    /**
     * 判断是否包含目标的三元组
     *
     * @param tuple ： 目标三元组
     * @return ： 若包含目标的三元组，返回true;否，返回false
     */
    @Override
    public boolean contains(AbstractTermTuple tuple) {
        return this.tuples.contains(tuple);
    }

    /**
     * 获得目标下标位置的三元组
     *
     * @param index：目标下标位置
     * @return: 三元组
     */
    @Override
    public AbstractTermTuple getTuple(int index) {
        return this.tuples.get(index);
    }

    /**
     * 返回文档对象包含的三元组的大小
     *
     * @return ：文档对象包含的三元组的大小
     */
    @Override
    public int getTupleSize() {
        return this.tuples.size();
    }

    /**
     * Document的toString方法覆盖
     *
     * @return ： Document的字符串表示
     */
    @Override
    public String toString() {
        return "Document{" +
                "docId=" + docId +
                ", docPath='" + docPath + '\'' +
                ", tuples=" + tuples +
                '}';
    }
}
