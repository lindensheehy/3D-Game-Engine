void project(Vec3* vec, Vec2* displayPos, Camera* camera, bool logVariables = false) {
    /*
        This returns a value between 0 and 1 which determines how far along each axis the given point should be drawn
        Can return values outside the 0-1 range, in this case the point lies off screen, but the location might still be needed
        These values are returned through the displayPos argument
    */

    if (logVariables) logWrite("--- Starting Projecting ---", true);

    if (logVariables) logVar("input vec x", vec->x);
    if (logVariables) logVar("input vec y", vec->y);
    if (logVariables) logVar("input vec z", vec->z);
    
    // Get points location relative to the cameras position and rotation
    Vec3* relative = vec->copy();
    relative->sub(camera->pos);
    relative->rotate(camera->yaw, 0, 0);
    relative->rotate(0, camera->pitch, 0);

    // If the point is behind the camera
    if (relative->z < 0) {
        delete relative;
        displayPos->x = -1;
        displayPos->y = -1;
        return;
    }

    // Find the distance along the x,z axis, and the dy from the camera to the vec, this is used to find pitch
    Vec2* tempVar = new Vec2(relative->x, relative->z);
    double dist = tempVar->magnitude();
    double dy = relative->y - camera->pos->y;
    delete tempVar;

    if (logVariables) logVar("dist", dist);
    if (logVariables) logVar("dy", dy);

    // Get the angle the point makes from the camera position on
    double angleYaw = getAngle(relative->x, relative->z);       // Angle from the +z axis
    double anglePitch = (double) 90 - getAngle(dist, dy);       // Angle from the +y axis, 90 - becuase its not against the axis used for getAngle

    // Gets the screen position given the angles found and the camera rotation angles
    /* ---  YAW  --- */

    double camYawFrom = -((double) camera->fov->x / 2);
    double camYawTo = ((double) camera->fov->x / 2);
    if (angleYaw > 180) {
        angleYaw -= 360;
    }

    if (logVariables) logVar("angle yaw", angleYaw);
    if (logVariables) logVar("cam yaw from", camYawFrom);
    if (logVariables) logVar("cam yaw to", camYawTo);

    double locationX = inRange(angleYaw, (double) -180, (double) 180);

    /* ---  PITCH  --- */
    double camPitchFrom = -(camera->fov->y / 2);
    double camPitchTo = (camera->fov->y / 2);
    if (anglePitch > 180) {
        anglePitch -= 360;
    }

    if (logVariables) logVar("angle pitch", anglePitch);
    if (logVariables) logVar("cam pitch from", camPitchFrom);
    if (logVariables) logVar("cam pitch to", camPitchTo);

    double locationY = inRange(anglePitch, (double) -180, (double) 180);

    // Value adjusting

    /*
        This code converts the range value between -180 and 180 into a value within the fov where values outside of 0-1 mean its outside the fov
        This is an extremely simplified version of the formula so it looks like nonsense but this is the math:
        First find the decimal value between -180 and 180 which represents the start of the fov
        value = (360 - k) / (2 * 360)
        The use this value so find the new decimal for the posision
        pos = (360 * (oldpos - value)) / fov
        so this all simplifies to the math below, with a lot of type casting because I dont trust cpp auto typing
    */

    locationX = (((double) 180 * ((double) 2 * locationX - (double) 1)) / camera->fov->x) + ((double) 0.5);
    locationY = (((double) 180 * ((double) 2 * locationY - (double) 1)) / camera->fov->y) + ((double) 0.5);

    if (logVariables) logVar("location x", locationX);
    if (logVariables) logVar("location y", locationY);

    displayPos->x = locationX;
    displayPos->y = locationY;

    return;
}