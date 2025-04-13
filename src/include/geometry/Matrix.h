#pragma once

#include "util/Utility.h"

#include "geometry/Vec.h"


namespace Geometry {

class Matrix4 {

    /*
        This is a class for 4x4 matrices
        Includes static functions for instantiating some standard matrices
        Also has instance functions for operations like matrix-matrix and vector-matrix multiplication
    */

    public:

        /*   Instance Variables   */

        float m[4][4];


        // Constructor (Uninitialized Values)
        Matrix4() {}


        /*   Instance Functions   */

        // Logs the matrix in a readable format
        void log();

        // Sets this Matrix4 to the given Matrix4
        void set(const Matrix4& other);
        void set(const Matrix4* other);

        // Mutliplies this Matrix4 by another Matrix4. Puts the result in this
        void mul(const Matrix4& other);
        void mul(const Matrix4* other);

        // Multiplies the given Vec3 by this Matrix4. Changes the contents of the Vec3
        void mul(Vec3* vec) const;


        /*   Class Functions   */

        // Loads the identity matrix into 'out'
        static void identity(Matrix4* out);

        // Loads a translation matrix by the given distance (x, y, z) into 'out'
        static void translation(float x, float y, float z, Matrix4* out);
        static void translation(const Vec3& vec, Matrix4* out);
        static void translation(const Vec3* vec, Matrix4* out);

        // Loads a scaling matrix by the given factors (x, y, z) into 'out'
        static void scaling(float x, float y, float z, Matrix4* out);
        static void scaling(const Vec3& vec, Matrix4* out);
        static void scaling(const Vec3* vec, Matrix4* out);

        // Loads a rotation matrix by the given angle around the X axis into 'out'. Uses degrees
        static void rotationX(float angle, Matrix4* out);

        // Loads a rotation matrix by the given angle around the Y axis into 'out'. Uses degrees
        static void rotationY(float angle, Matrix4* out);

        // Loads a rotation matrix by the given angle around the Z axis into 'out'. Uses degrees
        static void rotationZ(float angle, Matrix4* out);

        static void projection(float focalLengthX, float focalLengthY, Matrix4* out);

    private:

        // This function does the same as identity(), just it doesnt check for null ptr
        // Used so other static functions can make an identity matrix without the extra pointer check
        // All the other matrix loading functions call this, so its inlined for performance
        inline static void identityNoCheck(Matrix4* out) {

            /*
                NO NULLPTR CHECK!
                This function does not check if out is nullptr. This is why its private.
                Should only be called from within the class, and safely!
            */
        
            // This sets the matrix to all 0s
            // 0 in IEEE 754 is equivalent to all 0s (like 0x00000000), so this is an effective way to initialize the values
            memset(out->m, 0x00, sizeof(out->m));
        
            // Set 1s along the diagonal to make the identity matrix
            out->m[0][0] = 1.0f;
            out->m[1][1] = 1.0f;
            out->m[2][2] = 1.0f;
            out->m[3][3] = 1.0f;
        
            return;
        
        }

};

}
