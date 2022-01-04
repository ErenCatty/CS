package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;

/**
 * 测试搜索
 */
public class TestSearchIndex {
    /**
     *  搜索程序入口
     * @param args ：命令行参数
     */
    public static void main(String[] args){
        AbstractIndexSearcher indexSearcher=new IndexSearcher();
        indexSearcher.open(Config.INDEX_DIR+"index.dat");
        AbstractTerm queryTerm1=new Term("happy".toLowerCase());
        AbstractHit[] hits=indexSearcher.search(queryTerm1,new SimpleSorter());
        if(hits!=null){
            for(AbstractHit hit:hits)
                System.out.println(hit.getDocId()+":"+hit.getScore());
        }
    }
}
