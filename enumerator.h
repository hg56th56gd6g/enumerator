/*
枚举器的作用是获取(在列表arr中取l个可重复元素)的所有组合
即(有放回的有序抽样),组合的数量是len(arr)**l,枚举出每个组合的具体值
在枚举器的参数中,"组合"(缓冲区)由调用者提供,每"抽样完一组"就调用一次callback

举个例子
有一个列表arr=[0,1,2]
长度l=2
那么所有组合是:[
    [0,0],
    [0,1],
    [0,2],
    [1,0],
    [1,1],
    [1,2],
    [2,0],
    [2,1],
    [2,2]
]

当长度固定时(例子中为2)只需要这样写即可(python)
def Enumerator2(arr):
    #长度是多少就写几层循环,这里是2层
    for a in arr:
        for b in arr:
            yield a,b
for a in Enumerator2([0,1,2]):print(a)

但是如果长度不固定,就需要用递归才能比较简单
这个函数用更加高效的循环来解决这个问题
它可以用于穷举密码
参数示意(3长度):
_arr=[0,  1,  2,  3]
     arr            eoa

_buf=[None, None, None]#不需要初始化,由函数填充
     buf               eob
*/

//枚举器的回调函数类型,没有任何输入输出(因为缓冲区和长度由调用者提供),每完成一次枚举就会调用它
typedef void CALLBACK(void);
//枚举函数
void Enumerator(
    //要枚举的对象(void指针)列表
    void **arr,
    //列表的终止指针(不包括)
    void **eoa,
    //接收枚举结果的缓冲区
    void **buf,
    //缓冲区的终止指针(不包括)
    void **eob,
    //每次完成枚举的回调函数
    CALLBACK *Callback
){
    //检查参数,和两个代表当前buf,idx指针的变量
    if(eoa<=arr || eob<=buf)
        return;
    void **now_buf;
    void ***now_idx;
    //索引列表,储存了buf每个元素对应的arr索引
    //_idx=[&_arr[0], &_arr[0], &_arr[0]]#和buf长度一样
    //     idx                        eoi
    void **idx[eob-buf];
    //索引列表的终止指针(包括)
    void ***eoi=idx+(eob-buf-1);
    //初始化索引列表
    for(now_idx=idx;now_idx<=eoi;now_idx++)
        *now_idx=arr;

    for(;;){
        //更新缓冲区,然后调用Callback
        for(
            now_buf=buf,now_idx=idx;
            now_buf<eob;
            now_buf++,now_idx++
        )
            //从索引列表里逐个取值,然后将arr对应索引的值复制到buf
            *now_buf = **now_idx;
        Callback();

        //更新索引列表
        (*idx)++;
        for(
            now_idx=idx;
            //由于当前索引==最大索引时需要进位(下一个索引++)
            //那么就需要继续处理下一个索引,以及之后的索引
            //当一个索引没有进位,之后的也都不用处理了
            *now_idx==eoa;
        ){
            //当最后一个索引也进位,代表这个函数该结束了
            if(now_idx==eoi)
                return;
            //将当前索引设0,后一个索引++(进位)
            *now_idx=arr;
            now_idx++;
            (*now_idx)++;
        }
    }
}
//定义一个Enumerator模板的函数,Callback参数被去掉了
//name:要定义的函数名
//type:枚举的数据类型
//callback:每次完成枚举时执行这段代码
#define CreateEnumeratorFunction(name,type,callback) \
void name(\
    type *arr,\
    type *eoa,\
    type *buf,\
    type *eob\
){\
    if(eoa<=arr || eob<=buf)\
        return;\
    type *now_buf;\
    type **now_idx;\
    type *idx[eob-buf];\
    type **eoi=idx+(eob-buf-1);\
    for(now_idx=idx;now_idx<=eoi;now_idx++)\
        *now_idx=arr;\
    for(;;){\
        for(\
            now_buf=buf,now_idx=idx;\
            now_buf<eob;\
            now_buf++,now_idx++\
        )\
            *now_buf = **now_idx;\
        callback;\
        (*idx)++;\
        for(\
            now_idx=idx;\
            *now_idx==eoa;\
        ){\
            if(now_idx==eoi)\
                return;\
            *now_idx=arr;\
            now_idx++;\
            (*now_idx)++;\
        }\
    }\
}