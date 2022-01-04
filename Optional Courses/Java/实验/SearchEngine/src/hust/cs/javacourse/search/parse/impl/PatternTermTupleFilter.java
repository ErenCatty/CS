package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

/**
 * <pre>
 * PatternTermTupleFilter是抽象类AbstractTermTupleFilter的具体实现,里面包含另一个
 * AbstractTermTupleStream对象作为输入，并对输入的AbstractTermTupleStream进行过滤,
 * 例如过滤掉所有停用词（the，is are...)对应的三元组
 *
 * 基于正则表达式的过滤器
 * </pre>
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input){
        super(input);
    }

    /**
     * 获得下一个三元组
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next(){
        AbstractTermTuple abstractTermTuple=input.next();
        if(abstractTermTuple==null)
            return null;
        while(!abstractTermTuple.term.getContent().matches(Config.TERM_FILTER_PATTERN)){
            abstractTermTuple=input.next();
            if(abstractTermTuple==null)
                return null;
        }
        return abstractTermTuple;
    }
}