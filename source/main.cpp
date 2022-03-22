
    #include "Mathril.h"

    int main()
    {
       // Engine engine;
        //engine.loop();
        Mat4 mat;
        mat[0][1] = 24;
        mat[1][3] = 5;
        mat[2][0] = 7;

        std::cout << mat << std::endl;

        float* arr = (mat[0]);
        for(int i=0; i<16; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        return 0;
    }