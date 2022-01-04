package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.Sort;

import java.util.*;

/**
 * SimpleSorter具体实现了接口sort
 */
public class SimpleSorter implements Sort {
    /**
     * 对命中结果集合根据文档得分排序（从大至小）
     * @param hits ：命中结果集合
     */
    @Override
    public void sort(List<AbstractHit> hits){
        Collections.sort(hits, Comparator.reverseOrder());
    }

    /**
     * <pre>
     * score方法计算命中文档的得分，根据词条出现的频率进行赋值，返回得分的负值，
     * sort方法对传入的命中结果集合根据文档得分排序，需要注意的是两个词的搜索，这里采用了加和的方法，
     * 也即两个词的得分相加
     * @param hit ：命中文档
     * @return ：命中文档的得分
     * </pre>
     */
    @Override
    public double score(AbstractHit hit){
        double score=0;
        Set<AbstractTerm> key=hit.getTermPostingMapping().keySet();
        Iterator iterator=key.iterator();
        while(iterator.hasNext()){
            score+=hit.getTermPostingMapping().get(iterator.next()).getFreq();
        }
        return score;
    }
}