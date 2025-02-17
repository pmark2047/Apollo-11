/*************************************************************
 * 1. Name:
 *      Peyton Markus and Will Barr
 * 2. Assignment Name:
 *      Lab 02: Apollo 11 Physics
 * 3. Assignment Description:
 *      Simulate the Apollo 11 Lander
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part of this project was communication. This week
 *       one of us was sick and in Boise so we had to call and communicate
 *       well to finish the project within the time constraints
 * 5. How long did it take for you to complete the assignment?
 *      Roughly 2.5 hours
 **************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath> // for Triginometric Calculations
#include <string> // for string prompts

using namespace std;

// Set Global Variables
#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double s, double v, double a, double t)
{
   // return solution
   return (s + v * t + 0.5 * a * t * t);
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration(double f, double m)
{
   //return statement
   return (f/m);
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
   //return statement
   return (v + a * t);
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double a, double total)
{
   //return statement
   return (cos(a) * total);
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double computeHorizontalComponent(double a, double total)
{
   //return statement
   return (sin(a) * total);
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double x, double y)
{
   //return statement
   return sqrt((x * x + y * y));
}

/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radFromDeg(double d)
{
   return (2 * M_PI * (d/360.0));
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string prompt)
{
   double variable;
   cout << prompt;
   cin >> variable;
   return variable;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
   double dy = prompt("What is your vertical velocity (m/s)? ");  // Vertical Velocity
   double dx = prompt("What is your horizontal velocity (m/s)? ");   // Horizontal Velocity
   double y = prompt("What is your altitude (m)? ");  // Altitude (y)
   double x = 0;  // Position (x)
   double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");  // Angle (degrees)
   double t = 1; // Time (s)
   
    // Compute variables for calculation using the User's input
      // Angle in radians
   double aRadians = radFromDeg(aDegrees);
      // Acceleration due to thrust
   double accelerationThrust = computeAcceleration(THRUST, WEIGHT);
      // Horizontal acceleration due to thrust
   double ddxThrust = computeHorizontalComponent(aRadians, THRUST);
      // Vertical acceleration due to thrust
   double ddyThrust = computeVerticalComponent(aRadians, THRUST);
      // Total horizontal acceleration
   double ddx = computeAcceleration(ddxThrust, WEIGHT);
      // Total vertical acceleration
   double ddy = computeAcceleration(ddyThrust, WEIGHT) + GRAVITY;
      // Total velocity
   double v = computeTotalComponent(dx, dy);

   // Explain to User
   cout << "\nFor the next 5 seconds with the main engine on, "
   << "the position of the lander is:\n" << endl;
    // Go through the simulator five times
   for (int i = 0; i < 5; i++)
   {
      // Update Position
      x = computeDistance(x, dx, ddx, t);
      y = computeDistance(y, dy, ddy, t);
      
      // Update Velocity
      dx = computeVelocity(dx, ddx, t);
      dy = computeVelocity(dy, ddy, t);
      v = computeTotalComponent(dx, dy);

      
      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      cout << int (t * (i + 1)) << "s - x,y:(" << x << ", " << y << ")m  "
      << "dx,dy:(" << dx << ", " << dy << ")m/s  speed:"
      << v << "m/s  angle:"
      << aDegrees << "deg" << endl;
   }
   
   // Prompt for the new angle
   aDegrees = prompt("\nWhat is the NEW angle of the LM where 0 is up (degrees)? ");
   
   // Recompute the variables
   aRadians = radFromDeg(aDegrees);            // Angle in radians
   accelerationThrust = computeAcceleration(THRUST, WEIGHT);     // Acceleration due to thrust
   ddxThrust = computeHorizontalComponent(aRadians, THRUST);           // Horizontal acceleration due to thrust
   ddyThrust = computeVerticalComponent(aRadians, THRUST);             // Vertical acceleration due to thrust
   ddx = computeAcceleration(ddxThrust, WEIGHT);                 // Total horizontal acceleration
   ddy = computeAcceleration(ddyThrust, WEIGHT) + GRAVITY;                 // Total vertical acceleration
   v = computeTotalComponent(dx, dy);
   
   // Explain to User
   cout << "\nFor the next 5 seconds with the main engine on, the position of the lander is:\n" << endl;
   
   // Run through the simulator another 5 times for the new five seconds
   for (int i = 0; i < 5; i++)
   {
      // Update Position
      x = computeDistance(x, dx, ddx, t);
      y = computeDistance(y, dy, ddy, t);
      
      // Update Velocity
      dx = computeVelocity(dx, ddx, t);
      dy = computeVelocity(dy, ddy, t);
      v = computeTotalComponent(dx, dy);

      
      // Output
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      cout << int (t * (i + 6)) << "s - x,y:(" << x << ", " << y << ")m  "
      << "dx,dy:(" << dx << ", " << dy << ")m/s  speed:"
      << v << "m/s  angle:"
      << aDegrees << "deg" << endl;
   }

   return 0;
}
