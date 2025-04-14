auto drawNormal = [this](
    Geometry::Vec2& from, Geometry::Vec3& from3,
    Geometry::Vec2& to, Geometry::Vec3& to3
) {

    int distx = to.x - from.x;
    int disty = to.y - from.y;

    int totalDist = max(abs(distx), abs(disty));

    float x = from.x;
    float y = from.y;

    float totalDistFloat = (float) totalDist;
    float dx = distx / totalDistFloat;
    float dy = disty / totalDistFloat;

    for (int i = 0; i <= totalDist; i++) {

        this->pixelDrawer->drawPixel(Color::RED, (int) x, (int) y, 0, this->drawerOpacity);

        x += dx;
        y += dy;

    }

};

// Draw normal
Geometry::Vec3 normalStart3, normalEnd3;
normalStart3.set(triCenter);
normalEnd3.set(triCenter).add(mesh->transformedNormals[indexNormal]);

Geometry::Vec3 normalStartCopy, normalEndCopy;

normalStartCopy.set(normalStart3);
normalEndCopy.set(normalEnd3);
normalStartCopy.project();
normalEndCopy.project();

Geometry::Vec2 normalStart2, normalEnd2;

normalStart2.set(normalStartCopy.x, normalStartCopy.y);
normalEnd2.set(normalEndCopy.x, normalEndCopy.y);

this->display->toDisplayPos( &(normalStart2) );
this->display->toDisplayPos( &(normalEnd2) );

drawNormal(normalStart2, normalStart3, normalEnd2, normalEnd3);





/*
    Old draw tri function
*/

void Renderer::drawTri(
    uint32 color,
    Geometry::Vec2& a, Geometry::Vec3& a3,
    Geometry::Vec2& b, Geometry::Vec3& b3,
    Geometry::Vec2& c, Geometry::Vec3& c3
) {

    /*
        This works from left to right (+x direction) drawing vertical lines from the bounds of the triangle
        First find where each point stands in relation to eachother, then from the lowest x go to the highest x
    */

    // Lambda helper functions

    // Draws a straight line between two Vec2s. Assumes these are vertices in the triangle
    auto drawLine = [this, color](
        Geometry::Vec2& from, Geometry::Vec3& from3,
        Geometry::Vec2& to, Geometry::Vec3& to3
    ) {

        int distx = to.x - from.x;
        int disty = to.y - from.y;

        int totalDist = max(abs(distx), abs(disty));

        float x = from.x;
        float y = from.y;

        float totalDistFloat = (float) totalDist;
        float dx = distx / totalDistFloat;
        float dy = disty / totalDistFloat;

        float depth;
        Geometry::Vec3 depthVec;
        depthVec.set(from3);

        // Set up 'dDepthVec' (this is the amount 'depthVec' changes by on each iteration)
        Geometry::Vec3 dDepthVec;
        dDepthVec.set(to3).sub(from3).inverseScale(totalDistFloat);

        for (int i = 0; i <= totalDist; i++) {

            depth = depthVec.magnitude();

            this->pixelDrawer->drawPixel(color, (int) x, (int) y, depth, this->drawerOpacity);

            x += dx;
            y += dy;

            depthVec.add(dDepthVec);

        }

    };

    // Draws a straight line from (x, y1) to (x, y2)
    auto drawVerticalLine = [this, color, a, a3, b, b3, c, c3](
        int x, int y1, int y2
    ) {
        
        // Skip if this line is out of range
        if ( !this->pixelDrawer->inBufferRange(x, 0) ) return;

        // Clip y values to lie within the buffer
        this->pixelDrawer->clipCoordinates(&x, &y1);
        this->pixelDrawer->clipCoordinates(&x, &y2);

        // Use barycentric coords to find the 3d position of the start and end pixels
        Geometry::Vec3 p1;
        Geometry::Vec3 p2;
        {

            // General stuff
            float areaTotal = 0.5f * abs(
                (a.x * (b.y - c.y)) +
                (b.x * (c.y - a.y)) +
                (c.x * (a.y - b.y))
            );

            Geometry::Vec3 temp;
            float areaA, areaB, areaC;
            float lA, lB, lC;

            // Get first point (x, y1)
            areaA = 0.5f * abs(
                (x * (b.y - c.y)) +
                (b.x * (c.y - y1)) +
                (c.x * (y1 - b.y))
            );
        
            areaB = 0.5f * abs(
                (a.x * (y1 - c.y)) +
                (x * (c.y - a.y)) +
                (c.x * (a.y - y1))
            );
        
            areaC = 0.5f * abs(
                (a.x * (b.y - y1)) +
                (b.x * (y1 - a.y)) +
                (x * (a.y - b.y))
            );
        
            lA = areaA / areaTotal;
            lB = areaB / areaTotal;
            lC = areaC / areaTotal;
            
            temp.set(a3).scale(lA);
            p1.set(temp);

            temp.set(b3).scale(lB);
            p1.add(temp);

            temp.set(c3).scale(lC);
            p1.add(temp);

            // Get second point (x, y2)
            areaA = 0.5f * abs(
                (x * (b.y - c.y)) +
                (b.x * (c.y - y2)) +
                (c.x * (y2 - b.y))
            );
        
            areaB = 0.5f * abs(
                (a.x * (y2 - c.y)) +
                (x * (c.y - a.y)) +
                (c.x * (a.y - y2))
            );
        
            areaC = 0.5f * abs(
                (a.x * (b.y - y2)) +
                (b.x * (y2 - a.y)) +
                (x * (a.y - b.y))
            );
        
            lA = areaA / areaTotal;
            lB = areaB / areaTotal;
            lC = areaC / areaTotal;
            
            temp.set(a3).scale(lA);
            p2.set(temp);

            temp.set(b3).scale(lB);
            p2.add(temp);

            temp.set(c3).scale(lC);
            p2.add(temp);

        }
        
        // Edge case
        if (y1 == y2) {

            float depth = p1.magnitude();
            this->pixelDrawer->drawPixel(color, x, y1, depth, this->drawerOpacity);

            return;

        }

        if (y1 > y2) {

            swap(&y1, &y2);
        
            Geometry::Vec3 temp;
            temp.set(p1);
            p1.set(p2);
            p2.set(temp);

        }

        float depth;
        Geometry::Vec3 depthVec;
        depthVec.set(p1);

        // Set up 'dDepthVec' (this is the amount 'depthVec' changes by on each iteration)
        Geometry::Vec3 dDepthVec;
        dDepthVec.set(p2).sub(p1).inverseScale(y2 - y1);

        for (int i = y1; i <= y2; i++) {

            depth = depthVec.magnitude();

            this->pixelDrawer->drawPixel(color, x, i, depth, this->drawerOpacity);

            depthVec.add(dDepthVec);

        }

        return;

    };

    // Cases where the 'triangle' has more than one point with the same coordinates, so these are checked here for quick handling
    {    
        bool oneIsTwo = a.is(b);
        bool twoIsThree = b.is(c);
        bool oneIsThree = a.is(c);

        if ( oneIsTwo ) {

            // If two also equals three, all three coordinates are the same, so just return.
            // I should draw a single pixel in this case, but its not really worth it as it will barely be noticable
            if (twoIsThree) return;

            drawLine(a, a3, c, c3);
            return;

        }

        // Either of these cases draw the same line
        if ( oneIsThree || twoIsThree) {
            drawLine(a, a3, b, b3);
            return;
        }
    }


    // Sort the coordinates by their x values from least to greatest (left to right)
    {
        Geometry::Vec2 temp; Geometry::Vec3 temp3;

        if (b.x < a.x) {

            temp.set(a);
            a.set(b);
            b.set(temp);

            temp3.set(a3);
            a3.set(b3);
            b3.set(temp3);

        }

        if (c.x < a.x) {

            temp.set(a);
            a.set(c);
            c.set(temp);

            temp3.set(a3);
            a3.set(c3);
            c3.set(temp3);

        }

        if (c.x < b.x) {

            temp.set(b);
            b.set(c);
            c.set(temp);

            temp3.set(b3);
            b3.set(c3);
            c3.set(temp3);

        }
    }

    // These are the y values the line will go to/from for each x
    // The floats store the actual value, and the ints are rounded
    // The actual values may not actually be low and high as the names imply, and might be backwards, but logically it works the same
    float startY = a.y;
    float endY = a.y;
    int startYInt, endYInt;

    float slopeAB;
    float slopeBC;
    float slopeAC;

    bool invalidSlopeAB = false;
    bool invalidSlopeBC = false;
    bool invalidSlopeAC = false;


    // Slope between left-most point and the middle point
    if (a.x != b.x) slopeAB = (b.y - a.y) / (b.x - a.x);
    else invalidSlopeAB = true;

    // Slope between middle point and the right-most point
    if (b.x != c.x) slopeBC = (c.y - b.y) / (c.x - b.x);
    else invalidSlopeBC = true;

    // Slope between the left-most point and the right-most point
    if (a.x != c.x) slopeAC = (c.y - a.y) / (c.x - a.x);
    else invalidSlopeAC = true;


    // this checks if all the points have the same x coordinate and draws a single line accordingly (in two parts)
    // If the slope between 1 and 2, and the slope between 2 and 3 are both inf, theres no need to check the slope between 1 and 3.
    if (invalidSlopeAC) {

        if (a.y < b.y)
            drawVerticalLine(a.x, a.y, b.y);
        else
            drawVerticalLine(a.x, b.y, a.y);

        if (b.y < c.y)
            drawVerticalLine(a.x, b.y, c.y);
        else
            drawVerticalLine(a.x, c.y, b.y);

        return;

    }

    // From left to right until the mid vertex is hit
    if (!invalidSlopeAB) {

        int l = (int) a.x;
        int u = (int) b.x;

        for (int i = l; i < u; i++) {

            startY += slopeAB;
            endY += slopeAC;

            startYInt = (int) startY;
            endYInt = (int) endY;

            drawVerticalLine(i, startYInt, endYInt);

        }

    }
    
    // When the two left points have the same x, the startY and endY need to be adjusted becuase the first loop was skipped
    else {

        startY = (float) b.y;
        endY = (float) a.y;

    }
    
    // Carry on from the last loop
    if (!invalidSlopeBC) {

        int l = (int) b.x;
        int u = (int) c.x;

        for (int i = l; i < u; i++) {

            startY += slopeBC;
            endY += slopeAC;

            startYInt = (int) startY;
            endYInt = (int) endY;

            drawVerticalLine(i, startYInt, endYInt);

        }

    }

    return;

}






/*
    V2 draw tri
*/


void Renderer::drawTri(
    uint32 color,
    Geometry::Vec2& a, Geometry::Vec3& a3,
    Geometry::Vec2& b, Geometry::Vec3& b3,
    Geometry::Vec2& c, Geometry::Vec3& c3
) {

    /*
        This function uses a bounding box approach to fill the triangle
        It defines starting points, with some padding (see 'constexpr int padding')
        Then it uses the edge functions for each edge of the triangle to determine if the pixel lies within
        It also allows a little bit of leniency (see 'constexpr float leniency'), which helps fill gaps between triangles
    */

    // First find the bounding box of the triangle
    constexpr int padding = 1;
    int x1 = round( min(a.x, min(b.x, c.x)) ) - padding;
    int y1 = round( min(a.y, min(b.y, c.y)) ) - padding;
    int x2 = round( max(a.x, max(b.x, c.x)) ) + padding;
    int y2 = round( max(a.y, max(b.y, c.y)) ) + padding;

    // Break early if the triangle is unreasonably large (this means it lies outside the cameras FOV)
    // This will be replaced later with proper frustum culling, but it does the job for the time being
    constexpr int maxTriSize = 1024;
    if ( (x2 - x1 > maxTriSize) || (y2 - y1 > maxTriSize) ) return; 

    // Returns true if the pixel (x, y) lies within the triangle (a, b, c)
    auto insideTri = [a, b, c](
        int x, int y
    ) -> bool {

        // Get the edge function value for each line (a, b), (b, c), (c, a)
        float ab = ((b.x - a.x) * (y - a.y)) - ((b.y - a.y) * (x - a.x));
        float bc = ((c.x - b.x) * (y - b.y)) - ((c.y - b.y) * (x - b.x));
        float ca = ((a.x - c.x) * (y - c.y)) - ((a.y - c.y) * (x - c.x));

        // Pixels this far away the from the triangle will be counted
        constexpr float leniency = 0.8f;

        // Return true if they all share a sign. All positive or all negative
        return (
            (ab >= -leniency && bc >= -leniency && ca >= -leniency) ||
            (ab <= leniency && bc <= leniency && ca <= leniency) 
        );

    };


    // Some general stuff for finding barycentric coordinates in the loop
    float inverseAreaTotal = 1.0f / abs(
        (a.x * (b.y - c.y)) +
        (b.x * (c.y - a.y)) +
        (c.x * (a.y - b.y))
    );

    Geometry::Vec3 temp, depthVec;
    float areaA, areaB, areaC;
    float lA, lB, lC;

    float BsubC = b.y - c.y;
    float CsubA = c.y - a.y;
    float AsubB = a.y - b.y;

    // Loop over the previously defined bounds
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {

            // Skip iteration if the pixel is outside the triangle
            if ( !insideTri(i, j) ) continue;

            areaA = abs(
                (i * (BsubC)) +
                (b.x * (c.y - j)) +
                (c.x * (j - b.y))
            );
        
            areaB = abs(
                (a.x * (j - c.y)) +
                (i * (CsubA)) +
                (c.x * (a.y - j))
            );
        
            areaC = abs(
                (a.x * (b.y - j)) +
                (b.x * (j - a.y)) +
                (i * (AsubB))
            );
        
            lA = areaA * inverseAreaTotal;
            lB = areaB * inverseAreaTotal;
            lC = areaC * inverseAreaTotal;
            
            temp.set(a3).scale(lA);
            depthVec.set(temp);

            temp.set(b3).scale(lB);
            depthVec.add(temp);

            temp.set(c3).scale(lC);
            depthVec.add(temp);

            // Magnitude, but without the sqrt call
            float depth = (depthVec.x * depthVec.x) + (depthVec.y * depthVec.y) + (depthVec.z * depthVec.z);

            this->pixelDrawer->drawPixel(color, i, j, depth, this->drawerOpacity);

        }
    }

    return;

}
