package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.index.impl.IndexBuilder;
import hust.cs.javacourse.search.util.Config;

import java.io.File;

/**
 * 测试索引构建
 */
public class TestBuildIndex {
    /**
     *  索引构建程序入口
     *
     * @param args : 命令行参数
     */
    public static void main(String[] args){
        AbstractDocumentBuilder documentBuilder=new DocumentBuilder();
        AbstractIndexBuilder indexBuilder=new IndexBuilder(documentBuilder);
        String prescribedRoute=Config.DOC_DIR;
        System.out.println("Start index-building");
        AbstractIndex index1=indexBuilder.buildIndex(prescribedRoute);
        index1.optimize();
        System.out.println(index1);
        String indexFile=Config.INDEX_DIR+"index.dat";
        index1.save(new File(indexFile));
        AbstractIndex index2=new Index();
        index2.load(new File(indexFile));
        System.out.println("------------------");
        System.out.println(index2);
    }
}
