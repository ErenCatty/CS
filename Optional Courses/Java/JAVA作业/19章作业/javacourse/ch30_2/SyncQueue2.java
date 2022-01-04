package javacourse.ch30_2;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 一个线程安全同步队列，模拟多线程环境下的生产者消费者机制
 * 一个生产者线程通过produce方法向队列里产生元素
 * 一个消费者线程通过consume方法从队列里消费元素
 * @param <T> 元素类型
 */
public class SyncQueue2<T> {
    /**
     * 保存队列元素
     */
    private ArrayList<T> list = new ArrayList<>();
    private static Lock lock=new ReentrantLock();
    private static Condition newProduce=lock.newCondition();
    private static Condition newConsume=lock.newCondition();
    private int number=0;

    /**
     * 生产数据
     * @param elements  生产出的元素列表，需要将该列表元素放入队列
     * @throws InterruptedException
     */
    public void produce(List<T> elements) {
        lock.lock();    //acquire the lock
        try{
            //System.out.print("\nInto produce" + Thread.currentThread().getId()+" ");
            System.out.print("Produce elements:");
            for(int i=0;i<elements.size();i++)
                System.out.print(elements.get(i)+" ");
            number+= elements.size();
            System.out.println();
            for(int i=0;i< elements.size();i++)
                list.add(elements.get(i));
            //System.out.print("\nLeave produce" + Thread.currentThread().getId()+" ");
            newProduce.signalAll();
        } finally {
            lock.unlock();
        }
    }

    /**
     * 消费数据
     * @return 从队列中取出的数据
     * @throws InterruptedException
     */
    public List<T> consume() {
        lock.lock();
        List<T> list1 = null;
        try {
            //System.out.print("\nInto consume" + Thread.currentThread().getId()+" ");
            list1 = new ArrayList<>();
            while (number == 0) {
                //System.out.println("nothing to consume");
                //System.out.print("\nLeave consume" + Thread.currentThread().getId()+" ");
                newProduce.await();
            }
            //System.out.print("\nReenter consume" + Thread.currentThread().getId()+" ");
            for(int i=0;i<list.size();i++)
                list1.add(list.get(i));
            list.removeAll(list1);
            number=0;
            System.out.print("Consume elements:");
            for(int i=0;i< list1.size();i++)
                System.out.print(list1.get(i)+" ");
            System.out.println();
            //System.out.print("\nLeave consume" + Thread.currentThread().getId()+" ");
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
            return list1;
        }
    }
}