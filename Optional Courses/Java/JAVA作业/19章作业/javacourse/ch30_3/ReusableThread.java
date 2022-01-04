package javacourse.ch30_3;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReusableThread extends Thread{
    private Runnable runTask = null;  //保存接受的线程任务
    private static Lock lock=new ReentrantLock();
    private static Condition newSubmit=lock.newCondition();

    //只定义不带参数的构造函数
    public ReusableThread(){
        super();
    }

    /**
     * 覆盖Thread类的run方法
     */
    @Override
    public void run() {
        //这里必须是永远不结束的循环
        lock.lock();
        try{
            while(true){
                if(runTask!=null)
                    runTask.run();
                newSubmit.await();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally{
            lock.unlock();
        }
    }

    /**
     * 提交新的任务
     * @param task 要提交的任务
     */
    public void submit(Runnable task){
        lock.lock();
        try{
            runTask=task;
            newSubmit.signalAll();
        }
        finally {
            lock.unlock();
        }
    }
}

