package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.FileUtil;

import java.io.File;

/**
 * <pre>
 * AbstractIndexBuilder是索引构造器的抽象父类
 *      需要实例化一个具体子类对象完成索引构造的工作
 * </pre>
 */
public class IndexBuilder extends AbstractIndexBuilder {
    /**
     * 构造函数
     * @param docBuilder documentBuilder
     */
    public IndexBuilder(AbstractDocumentBuilder docBuilder) {
        super(docBuilder);
    }

    /**
     * 索引构造
     * @param specifiedDirectory
     * @return
     */
    public AbstractIndex buildIndex(String specifiedDirectory){
        AbstractIndex index=new Index();
        for(String path: FileUtil.list(specifiedDirectory)){
            AbstractDocument document=this.docBuilder.build(docId++,path,new File(path));
            index.addDocument(document);
        }
        index.save(new File(Config.INDEX_DIR+"index.dat"));
        return index;
    }
}
