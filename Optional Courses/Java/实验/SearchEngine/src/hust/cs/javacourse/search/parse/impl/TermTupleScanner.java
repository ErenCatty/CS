package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * <pre>
 *     TermTupleScanner是AbstractTermTupleScanner的具体实现，即一个具体的TermTupleScanner对象就是
 *     一个AbstractTermTupleStream流对象，它利用java.io.BufferedReader去读取文本文件得到一个个三元组TermTuple.
 *     具体地实现next方法获得文本文件里的三元组
 * </pre>
 */
public class TermTupleScanner extends AbstractTermTupleScanner {
    /**
     * 三元组保存list
     */
    private List<TermTuple> tuples=new ArrayList<>();

    /**
     * 三元组现保存位置
     */
    private int curPos;
    {
        curPos = 0;
    }

    /**
     * 缺省构造函数
     */
    public TermTupleScanner(){ }

    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     */
    public TermTupleScanner(BufferedReader input){
        super(input);
        try {
            String str=input.readLine();
            while(str!=null){
                StringSplitter stringSplitter=new StringSplitter();
                stringSplitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
                List<String> parts=stringSplitter.splitByRegex(str);
                for (String part : parts) {
                    if (!part.equals("")) {
                        this.tuples.add(new TermTuple(new Term(part.toLowerCase()), this.curPos++));
                    }
                }
                str=input.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 具体实现父类AbstractTermTupleStream的next方法
     */
    @Override
    public AbstractTermTuple next(){
        if(this.tuples.size()!=0){
            return tuples.remove(0);
        }
        else{
            return null;
        }
    }

}