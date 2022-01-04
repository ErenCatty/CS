package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.IndexBuilder;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import static hust.cs.javacourse.search.query.AbstractIndexSearcher.LogicalCombination.AND;
import static hust.cs.javacourse.search.query.AbstractIndexSearcher.LogicalCombination.OR;

/**
 * 搜索引擎具体实现类：菜单交互功能
 */
public class SearchSystem {
    /**
     * 菜单功能实现，实现交互功能
     * @param args 命令行参数
     */
    public static void main(String[] args){
        AbstractIndexBuilder indexBuilder=null;
        AbstractIndexSearcher indexSearcher=null;
        int op=1;    //用户输入项
        while(op!=0){
            System.out.println("------------------------------------");
            System.out.println("          Search Engine  ");
            System.out.println("          1.Save Index");
            System.out.println("          2.Load Index");
            System.out.println("          3.Search");
            System.out.println("          0.Exit");
            System.out.println("------------------------------------");
            System.out.println("Please input your option:");
            Scanner scanner=new Scanner(System.in);
            op=scanner.nextInt();
            switch(op){
                case 1:
                    if(indexBuilder==null){
                        AbstractDocumentBuilder documentBuilder=new DocumentBuilder();
                        indexBuilder=new IndexBuilder(documentBuilder);
                        String prescribedRoute= Config.DOC_DIR;
                        indexBuilder.buildIndex(prescribedRoute);
                        System.out.println("Index has been saved successfully.");
                    }
                    else{
                        System.out.println("Index saved.");
                    }
                    break;
                case 2:
                    if(indexSearcher==null){
                        String indexFile=Config.INDEX_DIR+"index.dat";
                        indexSearcher=new IndexSearcher();
                        indexSearcher.open(indexFile);
                        System.out.println("Index has been saved successfully.");
                    }
                    else
                        System.out.println("Index loaded.");
                    break;
                case 3:
                    if(indexSearcher==null){
                        System.out.println("Index needs to be built.");
                    }
                    else {
                        System.out.println("1.search in one word.");
                        System.out.println("2.search in wordA and wordB.");
                        System.out.println("3.search in wordA or wordB.");

                        int op2;
                        SimpleSorter simpleSorter=new SimpleSorter();
                        Scanner scanner1=new Scanner(System.in);
                        op2=scanner1.nextInt();

                        AbstractHit[] Hits;
                        AbstractTerm queryTerm1;
                        AbstractTerm queryTerm2;
                        Scanner scanner2=new Scanner(System.in);
                        switch (op2){
                            case 1:
                                System.out.print("Please input your key word: ");
                                queryTerm1 = new Term(scanner2.next());
                                if(isIllegal(queryTerm1))
                                    System.out.println("The word you input is illegal.");
                                else{
                                    Hits = indexSearcher.search(queryTerm1,simpleSorter);
                                    resultPrint(Hits);
                                }
                                break;
                            case 2:
                                System.out.print("Please input your key words: ");
                                queryTerm1=new Term(scanner2.next());
                                queryTerm2=new Term(scanner2.next());
                                if(isIllegal(queryTerm1)||isIllegal(queryTerm2))
                                    System.out.println("The word you input is illegal.");
                                else{
                                    Hits=indexSearcher.search(queryTerm1,queryTerm2,simpleSorter,AND);
                                    resultPrint(Hits);
                                }
                                break;
                            case 3:
                                System.out.print("Please input your key words: ");
                                queryTerm1=new Term(scanner2.next());
                                queryTerm2=new Term(scanner2.next());
                                if(isIllegal(queryTerm1)||isIllegal(queryTerm2))
                                    System.out.println("The word you input is illegal.");
                                else{
                                    Hits=indexSearcher.search(queryTerm1,queryTerm2,simpleSorter,OR);
                                    resultPrint(Hits);
                                }
                                break;
                            default:
                                System.out.println("False Input.");
                                break;
                        }
                    }
                    break;
                case 0:
                    break;
                default:
                    System.out.println("False Input.");
                    break;
            }
        }
    }

    /**
     * 搜索结果打印
     * @param Hits 搜索结果
     */
    public static void resultPrint(AbstractHit[] Hits){
        if(Hits.length==0){
            System.out.println("Not Found.");
        }
        else{
            for(AbstractHit hit:Hits){
                System.out.println("---------------------------------------------------------------------------");
                System.out.print("DocId:"+hit.getDocId()+":");
                System.out.println(hit.getDocPath());
                System.out.println(hit.getContent());
            }
            System.out.println();
        }
    }

    /**
     * 判断输入的单词是否合法
     * @param term 传入单词
     * @return 是否合法
     */
    public static boolean isIllegal(AbstractTerm term) {
        ArrayList<String> words = new ArrayList<>(Arrays.asList(StopWords.STOP_WORDS));
        boolean flag=words.contains(term.getContent());
        flag=flag && term.getContent().length() > Config.TERM_FILTER_MAXLENGTH
                && term.getContent().length() < Config.TERM_FILTER_MINLENGTH
                && !term.getContent().matches(Config.TERM_FILTER_PATTERN);
        return flag;
    }
}
