package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.FileSerializable;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * <pre>
 * Term是AbstractTerm对象的具体实现.
 *      Term对象表示文本文档里的一个单词.
 *      必须实现下面二个接口:
 *          Comparable：可比较大小（字典序）,为了加速检索过程，字典需要将单词进行排序.
 *          FileSerializable：可序列化到文件或从文件反序列化.
 *   </pre>
 */
public class Term extends AbstractTerm implements Comparable<AbstractTerm>, FileSerializable {
    /**
     * 缺省构造函数
     */
    public Term(){ }

    /**
     * 构造函数
     *
     * @param content Term内容
     */
    public Term(String content){
        this.content=content;
    }

    /**
     * 判断二个Term内容是否相同
     *
     * @param obj ：要比较的另外一个Term
     * @return 如果内容相等返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj){
        if(obj instanceof Term){
            Term term=(Term) obj;
            return term.content.equals(this.content);
        }
        return false;
    }

    /**
     * 返回Term的字符串表示
     *
     * @return 字符串
     */
    @Override
    public String toString(){
        return this.content;
    }

    /**
     * 返回Term内容
     *
     * @return Term内容
     */
    public String getContent(){
        return this.content;
    }

    /**
     * 设置Term内容
     *
     * @param content：Term的内容
     */
    public void setContent(String content){
        this.content=content;
    }

    /**
     * 比较二个Term大小（按字典序）
     *
     * @param o： 要比较的Term对象
     * @return ： 返回二个Term对象的字典序差值
     */
    @Override
    public int compareTo(hust.cs.javacourse.search.index.AbstractTerm o) {
        return this.getContent().compareTo(o.getContent());
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    public void writeObject(ObjectOutputStream out){
        try {
            out.writeObject(this.content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    public void readObject(ObjectInputStream in){
        try {
            this.content=(String)in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
