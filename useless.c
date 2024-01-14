#include <stdio.h>

int (*(*(*myBestFunc())[5][1][2][3])())()
{
    int myfunc4();
    static int (*(*(myArr[5][1][2][3]))())() = {myfunc4};
    return myArr;
}

int main()
{
    // eger bir gun gereksiz hissedersen boyle bir degisken tanimi oldugunu hatirla
    // on one day if you ever feel useless remember this variable declaration exists
    int myfunc();
    int (*myfunc_p)();
    int (*(*myfunc_pp)())();
    int (*(*(*myfunc_ppp)())())();
    int (*(*(*(*myVar)())[5][1][2][3])())();
    myVar = myBestFunc();
    int c = (*(*myBestFunc)())[0][0][0][0]()();
    printf("%d\n", c);
}

int myfunc4()
{
    return 1;
}