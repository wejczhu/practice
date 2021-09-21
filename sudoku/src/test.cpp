#include "test.h"
#include <time.h>
#include <iostream>

using namespace std;

void test_case1()
{
    SceneC scene;

    time_t begin, end;
    time(&begin);
    scene.Generate();
    time(&end);

    scene.Show();
    cout << end - begin << end;
}