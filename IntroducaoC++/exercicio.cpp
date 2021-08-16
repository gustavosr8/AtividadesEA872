#include <iostream>

class coord{
    private:
        int x,y;
    public:
        coord(int new_x,int new_y);
};

coord::coord(int new_x, int new_y){
    x=new_x;
    y=new_y;
}


class cube{
    private:
        int x,y,z;  
    public:
        cube(int new_x, int new_y, int new_z);
        void cube_print_volume();
};

cube::cube(int new_x, int new_y, int new_z){
    x=new_x;
    y=new_y;
    z=new_z;
}

void cube::cube_print_volume(){
    std::cout << x*y*z << std::endl; 
}

int main(){


    coord *c1 = new coord(50,10);
    cube *c2  = new cube(10,20,30);
    c2->cube_print_volume();

    delete c1;
    delete c2;

    return 0;
}