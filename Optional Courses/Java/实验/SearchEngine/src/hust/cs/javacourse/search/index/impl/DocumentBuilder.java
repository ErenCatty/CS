package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;

import java.io.*;

/**
 * <pre>
 *     DocumentBuilder是AbstractDocumentBuilder类的具体实现，是Document构造器类.
 *     Document构造器的功能应该是由解析文本文档得到的TermTupleStream，产生Document对象.
 * </pre>
 */
public class DocumentBuilder extends AbstractDocumentBuilder {
    /**
     * 缺省构造函数
     */
    public DocumentBuilder(){}

    /**
     * <pre>
     * 由解析文本文档得到的TermTupleStream,构造Document对象.
     *
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return ：Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId,
                                  String docPath,
                                  AbstractTermTupleStream termTupleStream){
        AbstractDocument document=new Document(docId,docPath);
        AbstractTermTuple termtuple= termTupleStream.next();
        while(termtuple!=null){
            document.addTuple(termtuple);
            termtuple=termTupleStream.next();
        }
        termTupleStream.close();
        return document;
    }

    /**
     * <pre>
     * 由给定的File,构造Document对象.
     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,内部调用
     *      AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream)
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return          : Document对象
     * </pre>
     */
    public AbstractDocument build(int docId, String docPath, File file){
        AbstractTermTupleStream termTupleStream;
        BufferedReader reader= null;
        try {
            reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        termTupleStream=new LengthTermTupleFilter(new StopWordTermTupleFilter(new PatternTermTupleFilter(new TermTupleScanner(reader))));
        return this.build(docId,docPath,termTupleStream);
    }
}