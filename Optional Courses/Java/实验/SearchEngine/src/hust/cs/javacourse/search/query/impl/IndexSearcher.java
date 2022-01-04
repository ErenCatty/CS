package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;

import java.io.File;
import java.util.*;

/**
 * <pre>
 *     IndexSearcher是AbstractIndexSearcher的具体实现
 *     AbstractIndexSearcher是检索具体实现的抽象类
 * </pre>
 */
public class IndexSearcher extends AbstractIndexSearcher {
    /**
     * 缺省构造函数
     */
    public IndexSearcher(){}

    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile){
        this.index.load(new File(indexFile));
    }

    /**
     * 根据单个检索词进行搜索
     *
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return ：命中结果数组
     */
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter){
        AbstractPostingList postinglist=this.index.search(queryTerm);
        if(postinglist!=null){
            Map<AbstractTerm, AbstractPosting> termPostingMap=new HashMap<>();
            AbstractHit[] hits=new AbstractHit[postinglist.size()];
            for(int i=0;i<postinglist.size();i++){
                AbstractPosting posting=postinglist.get(i);
                termPostingMap.put(queryTerm,posting);
                hits[i]=new Hit(posting.getDocId(),this.index.getDocName(posting.getDocId()),termPostingMap);
                hits[i].setScore(sorter.score(hits[i]));
                termPostingMap.clear();
            }
            sorter.sort(Arrays.asList(hits));
            return hits;
        }
        else
            return null;
    }

    /**
     *
     * 根据二个检索词进行搜索
     *
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    public AbstractHit[] search(AbstractTerm queryTerm1,
                                AbstractTerm queryTerm2,
                                Sort sorter,
                                LogicalCombination combine){
        AbstractPostingList postinglist1=this.index.search(queryTerm1);
        AbstractPostingList postinglist2=this.index.search(queryTerm2);
        Map<AbstractTerm,AbstractPosting> termPostingMap=new HashMap<>();
        ArrayList<AbstractHit> hits=new ArrayList<>();
        switch(combine){
            case OR:
                if(postinglist1!=null){
                    for(int i=0;i<postinglist1.size();i++){
                        AbstractPosting posting=postinglist1.get(i);
                        termPostingMap.put(queryTerm1,posting);
                        hits.add(new Hit(posting.getDocId(),
                                this.index.getDocName(posting.getDocId()),
                                termPostingMap));
                        hits.get(i).setScore(sorter.score(hits.get(i)));
                        termPostingMap.clear();
                    }
                }
                if(postinglist2!=null){
                    for(int i=0;i<postinglist2.size();i++){
                        int flag=0;
                        AbstractPosting posting=postinglist2.get(i);
                        for(int j=0;j<hits.size();j++){
                            AbstractHit abstractHit=hits.get(i);
                            if(abstractHit.getDocId()==posting.getDocId()){
                                abstractHit.getTermPostingMapping().put(queryTerm2,posting);
                                abstractHit.setScore(sorter.score(abstractHit));
                                flag=1;
                            }
                        }
                        if(flag==0){
                            termPostingMap.put(queryTerm2,posting);
                            hits.add(new Hit(posting.getDocId(),this.index.getDocName(posting.getDocId()),termPostingMap));
                            hits.get(hits.size()-1).setScore(sorter.score(hits.get(hits.size()-1)));
                            termPostingMap.clear();
                        }
                    }
                }
                break;
            case AND:
                if(postinglist1!=null&&postinglist2!=null){
                    for(int i=0;i<postinglist1.size();i++){
                        AbstractPosting posting1=postinglist1.get(i);
                        for(int j=0;j<postinglist2.size();j++){
                            AbstractPosting posting2=postinglist2.get(j);
                            if(posting1.getDocId()==posting2.getDocId()){
                                termPostingMap.put(queryTerm1,posting1);
                                termPostingMap.put(queryTerm2,posting2);
                                hits.add(new Hit(posting1.getDocId(),this.index.getDocName(posting1.getDocId()),termPostingMap));
                                hits.get(i).setScore(sorter.score(hits.get(i)));
                                termPostingMap.clear();
                            }
                        }
                    }
                }
                break;
        }
        sorter.sort(hits);
        AbstractHit[] newhits=new AbstractHit[hits.size()];
        return hits.toArray(newhits);
    }
}