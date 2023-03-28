#include<gl/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

struct Point {
    float x, y, z;
};
void LoadIdentity(float b[4][4]) // 初始化单位矩阵
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
        {
            if (i != j)b[i][j] = 0;
            else b[i][j] = 1;
            //cout << b[i][j] << " ";
        }
        //cout << endl;
    }
}
class TDTransform
{
public:
    bool flag;
    float cube[8][4];// 坐标矩阵
public :
    void Translate(float x,float y , float z);
    void Scale(float x, float y, float z);
    void revolve(Point a,Point b);
    void duichen(int x);
    void cuoqie(int op,float x, float y);
    void Drawcube();
    void mul(float b[][4]);
    void init();
};
TDTransform tran;
void TDTransform::duichen(int x)
{
    glMatrixMode(GL_MODELVIEW);
    if (!flag)
    {
        glColor3f(1, 0, 0);
        glTranslated(-1, 0, -10);
        Drawcube();
        flag = 1;
    }
    float b[4][4];
    // 变换矩阵
    LoadIdentity(b);
    if(x == 1) b[1][1] = -1, b[2][2] = -1;
    else if(x == 2)b[0][0] = -1, b[2][2] = -1;
    else if(x == 3)b[0][0] = -1, b[1][1] = -1;
    
    
    mul(b);
    glColor3f(0, 1, 0);
    Drawcube();
    glFlush();
}
void TDTransform::cuoqie(int op,float x, float y)
{
    glMatrixMode(GL_MODELVIEW);

    float b[4][4];
    if (!flag)
    {
        glColor3f(1, 0, 0);
        glTranslated(-1, 0, -10);
        Drawcube();
        flag = 1;
    }
    // 变换矩阵
    LoadIdentity(b);
    if (op == 1) b[1][0] = x, b[2][0] = y;
    else if (op == 2)b[0][1] = x, b[2][1] = y;
    else if (op == 3)b[0][2] = x, b[1][2] = y;


    mul(b);
    glColor3f(0, 1, 0);
    Drawcube();
    glFlush();
}
void TDTransform::init()
{
    flag = false;
    cube[0][0] = 0, cube[0][1] = 0, cube[0][2] = 0,cube[0][3] = 1;
    cube[1][0] = 0, cube[1][1] = 0, cube[1][2] = 1,cube[1][3] = 1;
    cube[2][0] = 1, cube[2][1] = 0, cube[2][2] = 1,cube[2][3] = 1;
    cube[3][0] = 1, cube[3][1] = 0, cube[3][2] = 0,cube[3][3] = 1;
    
    cube[4][0] = 0, cube[4][1] = 1, cube[4][2] = 0,cube[4][3] = 1;
    cube[5][0] = 0, cube[5][1] = 1, cube[5][2] = 1,cube[5][3] = 1;
    cube[6][0] = 1, cube[6][1] = 1, cube[6][2] = 1,cube[6][3] = 1;
    cube[7][0] = 1, cube[7][1] = 1, cube[7][2] = 0,cube[7][3] = 1;
}
void TDTransform::Drawcube()
{
    glBegin(GL_LINES); //画上面的那个面
    glVertex3f(cube[4][0], cube[4][1], cube[4][2]);
    glVertex3f(cube[5][0], cube[5][1], cube[5][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[4][0], cube[4][1], cube[4][2]);
    glVertex3f(cube[7][0], cube[7][1], cube[7][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[7][0], cube[7][1], cube[7][2]);
    glVertex3f(cube[6][0], cube[6][1], cube[6][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[5][0], cube[5][1], cube[5][2]);
    glVertex3f(cube[6][0], cube[6][1], cube[6][2]);
    glEnd();

    glBegin(GL_LINES);//画下面的那个面
    glVertex3f(cube[0][0], cube[0][1], cube[0][2]);
    glVertex3f(cube[1][0], cube[1][1], cube[1][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[0][0], cube[0][1], cube[0][2]);
    glVertex3f(cube[3][0], cube[3][1], cube[3][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[3][0], cube[3][1], cube[3][2]);
    glVertex3f(cube[2][0], cube[2][1], cube[2][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[1][0], cube[1][1], cube[1][2]);
    glVertex3f(cube[2][0], cube[2][1], cube[2][2]);
    glEnd();

    glBegin(GL_LINES);// 画中间的四个面
    glVertex3f(cube[0][0], cube[0][1], cube[0][2]);
    glVertex3f(cube[4][0], cube[4][1], cube[4][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[1][0], cube[1][1], cube[1][2]);
    glVertex3f(cube[5][0], cube[5][1], cube[5][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[3][0], cube[3][1], cube[3][2]);
    glVertex3f(cube[7][0], cube[7][1], cube[7][2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(cube[2][0], cube[2][1], cube[2][2]);
    glVertex3f(cube[6][0], cube[6][1], cube[6][2]);
    glEnd();
    glFlush();
}
void TDTransform::mul(float b[][4])
{
    float c[8][4];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 4; j++) {
            c[i][j] = 0;
        }
    for(int i = 0; i < 8; i ++)
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            for (int k = 0; k < 4; k++)
            {
                sum += cube[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            cube[i][j] = c[i][j];
            //cout << cube[i][j] << " ";
        }
        //cout << endl;
    }
}
void TDTransform::Translate(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    // 变换矩阵,为了能够清楚的看清，首先先移动下坐标轴
    
     glColor3f(1, 0, 0);
     glTranslated(-2, 0, -20);
     Drawcube();
     flag = 1;
    
    float b[4][4];
    // 变换矩阵
    LoadIdentity(b);
    b[3][0] = x, b[3][1] = y, b[3][2] = z;
    // 画出平移后的正方体
    mul(b);
    glColor3f(0, 1, 0);
    Drawcube();
    glFlush();
}
void TDTransform::Scale(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    
    if (!flag)
    {
        glColor3f(1, 0, 0);
        glTranslated(-1, 0, -10);
        Drawcube();
        flag = 1;
    }
    float b[4][4];
    LoadIdentity(b);
    if (fabs(x - 0) > 1e-5) b[0][0] = x;
    if (fabs(y - 0) > 1e-5) b[1][1] = y;
    if (fabs(z - 0) > 1e-5) b[2][2] = z;
    //cout << b[0][0] << " " << b[1][1] << " " << b[2][2] << endl;
    mul(b);
    glColor3f(0, 1, 0);
    Drawcube();
    glFlush();
}
void TDTransform::revolve(Point a, Point b)
{
    glMatrixMode(GL_MODELVIEW);
    if (!flag)
    {
        glColor3f(1, 0, 0);
        glTranslated(-1, 0, -10);
        //Drawcube();
        flag = 1;
    }
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    //绘制出旋转轴
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glEnd();
    glColor3f(1, 0, 0);
    //先将旋转轴转到y0z平面，再将他转到与y轴重合
    float zz, xx;
    if (fabs(b.y - 0) > 1e-5)zz = atan(b.x / b.y); //绕z轴旋转角度
    else zz = 90;
    if (fabs(b.y - a.y) > 1e-5 || fabs(b.x - a.x) > 1e-5) xx = atan(b.z / sqrt(b.x * b.x + b.y * b.y));//绕x轴的旋转角度
    else xx = 90;
   
    float c[7][4][4];
    
    for (int i = 0; i < 10; i++)
    {
        //逆变换
        //初始化单位矩阵
        for (int i = 0; i < 7; i++) LoadIdentity(c[i]);
        //平移
        c[0][3][0] = -a.x ,c[0][3][1] = -a.y,c[0][3][2] = -a.z;
        mul(c[0]);
        //绕z旋转
        c[1][0][0] = cos(zz), c[1][0][1] = sin(zz);
        c[1][1][0] = -sin(zz), c[1][1][1] = cos(zz);
        mul(c[1]);
        //绕x旋转
        c[2][1][1] = cos(-xx), c[2][1][2] = sin(-xx);
        c[2][2][1] = -sin(-xx), c[2][2][2] = cos(-xx);
        mul(c[2]);
        // 绕y坐标轴旋转
        c[3][0][0] = cos(36), c[3][0][2] = -sin(36);
        c[3][2][0] = sin(36), c[3][2][2] = cos(36);
        mul(c[3]);
        //逆操作
        c[4][1][1] = cos(xx), c[4][1][2] = sin(xx);
        c[4][2][1] = -sin(xx), c[4][2][2] = cos(xx);
        mul(c[4]);

        c[5][0][0] = cos(-zz), c[5][0][1] = sin(-zz);
        c[5][1][0] = -sin(-zz), c[5][1][1] = cos(-zz);
        mul(c[5]);
        
        c[6][3][0] = a.x, c[6][3][1] = a.y, c[6][3][2] = a.z;
        mul(c[6]);
        Drawcube();
    }
    glFlush();
}


void transl() {
    cout << "请输入三维平移向量(x,y,z):";
    float x, y, z;
    cin >> x >> y >> z;
    tran.Translate(x, y, z);
}
void scal() {
    cout << "请输入三维放缩向量(x,y,z):";
    float x, y, z;
    cin >> x >> y >> z;
    tran.Scale(x, y, z);
}
void revolve() {
    Point p, p1;
    cout << "请输入三维旋转轴[Point(x,y,z)，Point1(x,y,z)]: ";
    cin >> p.x >> p.y >> p.z;
    cin >> p1.x >> p1.y >> p1.z;
    tran.revolve(p,p1);
}
void cuoq() {
    cout << "请输入错切的坐标轴以及另外两个错切值(1:x,2:y,3:z):";
    float a,b;
    int op;
    cin >> op >> a >> b;
    tran.cuoqie(op, a, b);
}
void duic() {
    cout << "请输入对称轴(1:x,2:y,3:z):";
    int op;
    cin >> op;
    tran.duichen(op);
}
void display()
{
    tran.init();
    
    while (true)
    {

        cout << "1. 图形平移" << endl;
        cout << "2. 图形放缩" << endl;
        cout << "3. 图形旋转" << endl;
        cout << "4. 图形错切" << endl;
        cout << "5. 图形对称" << endl;
        cout << "请输入功能编号：";
        int op;
        cin >> op;
        switch (op)
        {
        case  1: {transl(); break; } // 3,0,0
        case  2: {scal(); break; }   // 1.5 1.5 1.5
        case  3: {revolve(); break; } //-25 -30 -25 20 15 20;
        case  4: {cuoq(); break; }
        case  5: {duic(); break; }
        default:
            break;
        }
        cout << endl;
    }
}
int main(int argc, char** argv)
{
    //以屏幕中心为原点(0,0,0)，当你面对屏幕时，
    //右边是X正轴，上方是Y轴正轴，屏幕指向你的方向为Z轴正轴。
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("三维图形变换");

    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0, 100);

    glutDisplayFunc(display);
    glutMainLoop();

}

/*
1 1 1
2 2 2
0.2 0.3 0.4
-1 -5 -7 2 3 6
1 2 0 
*/