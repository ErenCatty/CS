package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

/**
 * <pre>
 * StopWordTermTupleFilter是抽象类AbstractTermTupleFilter的具体实现,里面包含另一个
 * AbstractTermTupleStream对象作为输入，并对输入的AbstractTermTupleStream进行过滤,
 * 例如过滤掉所有停用词（the，is are...)对应的三元组
 *
 * 停用词的过滤器
 * </pre>
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 停用词集合
     */
    private List<String> stopWord;

    /**
     * 构造函数
     *
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input){
        super(input);
        this.stopWord = new ArrayList<>(Arrays.asList(StopWords.STOP_WORDS));
    }

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next(){
        AbstractTermTuple stopwordtermtuplefilter=input.next();
        if(stopwordtermtuplefilter==null)
            return null;
        while(stopWord.contains(stopwordtermtuplefilter.term.getContent())){
            stopwordtermtuplefilter=input.next();
            if(stopwordtermtuplefilter==null)
                return null;
        }
        return stopwordtermtuplefilter;
    }
}
