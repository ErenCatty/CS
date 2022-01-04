package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

/**
 * <pre>
 * LengthTermTupleFilter是抽象类AbstractTermTupleFilter的具体实现,里面包含另一个
 * AbstractTermTupleStream对象作为输入，并对输入的AbstractTermTupleStream进行过滤,
 *
 * 过滤掉过长或过短的单词的过滤器
 * </pre>
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input){
        super(input);
    }

    /**
     * 获得下一个三元组
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple result = null;
        boolean finished = false;
        AbstractTermTuple abstractTermTuple = input.next();
        if (abstractTermTuple != null) {
            while (abstractTermTuple.term.getContent().length() > Config.TERM_FILTER_MAXLENGTH
                    || abstractTermTuple.term.getContent().length() < Config.TERM_FILTER_MINLENGTH) {
                abstractTermTuple = input.next();
                if (abstractTermTuple == null) {
                    finished = true;
                    break;
                }
            }
            if (!finished) {
                result = abstractTermTuple;
            }
        }
        return result;
    }
}
