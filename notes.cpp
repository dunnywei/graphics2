/*
		Lec 10(01:29)->Shader is a program executed on the graphic card
		Currently, the foloinwg code is executed on the CPU
		->Shader goes to the graphic pipeline.
		->We need to customerize the piplelie
        ->(02:32) Shader's responsiblity is to shade the pixel
        ->(02:57) Vertex shader and fragment shader(pixel) (3:31) 
        ->(03:55) While hitting glDrawElements, Opengl will take its vertex into vertex shader in order
        -> Vertex shader has to output two things:positions on the screen and any other thing(custom data)(4:26)
        ->Once the OpenGl has the position (3 vertices) making one triangle
        ->(4:35) If the OpenGL wishes to draw the triangle, it has to fill every single pixes 
        //inside that triangle
        -> (4:55) Every single pixel(framgent), OpenGl has to execute fragment shader
        -> (5:13) For the vertex shader, it needs to run 5 times
        -> (5:22) for the fragment shader, it needs to run several times depending on 
        # of framents in the triangle
        ->(5:31) Postion data from OpenGl(GPU)
        ->(5:38) The custom data comes back in to the fragment shader
        ->(5:40) The GPU interpolate the data from vertex to vertex
        ->(5:51) The triangle (left is blue, down is red) so it will blend
        from blue to red eventually from top to buttom
        -> (6:18) We need to write the fragment shader which will run the CPU
        at the end
        -> (6:20) The only thing fragment shader has to output is R,G,B,A color
        -> (6:35) We know who much does each RGB color applies to each fragment
        in every single pixel
        -> (7:18) GPU is super powerful since they do in parallel. It means GPU is
        good to do the floating point arithmatic including vector math

       ->(7:48) GPU load several vertex(in our case verts[]) in parallel
*/

/*Lecture_14
-how many times does vertex shader execute? (00:36)
-Three times since there are only three vertexes (0:45)
-How many times does fragement shader execute? (00:53)
-There are a lot of fragments (pixels) required to draw (1:11)
-For now we assume fragments and pixels are the same
-how does hardware know what value to pass to the fragment shader(1:36)
-For the triangle, we have top bue,left buttom green and right buttom red (1:56)
-hardware will interpolate between two points. There is a video named lerp for linear interplation(2:03)
-blends=interpolate between the value (02:12) 
-When we send the data out of the vertex shader, the hardware do the interpolation(blend) (2:28)
-Should watch lerp video fro jamie king (3:49)
*/

/*Lecture 15
-it is like using OO concept (01:26)
-GLuint vertexShaderID is like a handler. Treat them as pointer of an object (01:56)
-think them as OO programming (6:33)
|*/

/*Lecture 16
-when we use glCompileShader, we want to see the error message (1:16)
-Need to check if coppile works (1:26)
*/

/*Lecture 18
-raadShaderCode(""); (1:37)(1:49)

*/

/*Lecture 19_OpenGL Fragment vs Pixel
-Fragment=potential pixel (0:23)
-fragment shader kicks out a RGBA value (0:37). This value may not be necessary shown up on the screen as a pixel(0:39)(0:41)
-Think fragment as a caterpillars and may potenally become a butterfy (0:51) if it succeeds (2:02)
-Output as a RGBA value but doesn't mean it is a pixel (1:08)
-draw red triangle then draw blue triangle. The red will overwrites blue when there is overlapping 
Painter algorithm(2:17)
-In order to have the red again. It required to draw red again (2:23)
-We need to make sure the red precedence over the blue triangle (3:12)
-Or red triangle is closer to the viewer than blue triangle (3:18)(3:24)
-(3:40)The precedence of red over blue is that when the OpenGL try to draw red but see the blue,
it will keep the red. Otherwise draw blue (4:16)
-When OpenGL try to fill the blue pixels from RGB value from fragment shader (5:16), I can't
draw you due to the red color has precedence over blue color (5:21)
-Some of fragments become pixels (5:41) but not all of the do
-the dpeth in OpenGL deals with the which color has the precedence (5:52)
*/

/*Lecture 20_OpenGL Depth Buffer
->x from left to right
->y from buttom to top
->z axis (0:53), coming straight out of the screen as -ve, (going in to the screen is +ve)->important (1:08)
->on Z axis the +1 is too far to see and -1 is too close to see(like clipping) (2:41)
->The vertex with greater Z value is further away from us or camer (3:27) with more depth (3:30)
->IF you are close to the camera or us you have less z value with less depth (3:37)
->If I give the red triangle with less depth so it will be closer to the camera or scene. It will 
be always on top of the blue triangle (3:56)
->we need to cover buffer(4:05)
->An image is a 2D array of pixels (4:08)
->No matter if it is a 2D or 3D image, it is a 2D dimension array of pixel (4:20)
->A pixel contains r,g,b values (4:24)
->two dimension array of triangle (4:57)
->We put the color including RGB into the buffer then dispalyed on the screen (6:03)
->We also have to worry about is the depth buffer (6:08)
->Dpeth buffer is also a 2D array (6:13) and storing one values (6:15). Dpeth of the
fragment (6:22)
->For example in both triangle, our case always make z=0 in vertex shader(6:28)(6:40)
->It makes every z=0 in this scene (6:44)
as 
gl_Position=vec4(position,0.0,1.0);
   //Lecture 20->specifiy the z value is always 0 (3:18)
->The z value has nothing to do with position (6:50) will be shown up on the screen (6:52)
->The only thing the OpenGL z value is used for (6:55) is the depth
->x and y (6:59) determine the where vertex will be displayed on the screen (7:02) z-value
determines the dpeth
->In default, the depth buffer is not turned on (7:10)(7:31)
->When we begin to render the scene, we want to make the farest depth (7:35)
->So we make our depth as +1 as the farest depth (8:06)
->When we try to render the scene, all of the RGB's color is 0 and we will try to clear out the buffer
as well (8:27)
->so we make 0,0,0 for RGB color (8:34)
->The z value for red triangle (8:44) to -0.5 so it is closer to the screen
->The z value for blue traingle (8:58) to +0.5 (9:02) so it is further to the screnn (9:05)
->we try to render both triangles(9:13)
->Red triangle will be rendered first (9:16)
->let's us pick the center. Now it is 000 in RGB befoe rendering red (9:26)
->Now it is 100 in RGB while rendering red(9:37).It is a fragment having a potential to
become pixel (9:41) 
->what's the depth of this fragment(9:46)? OpenGL looks at three vertices make the
triangle(9:49) then interpret the z depth(9:51) as three vertrices (9:54)
->since z value is for red triangle is 0.5 (10:02) so all the fragment inside the red triangle
has to be -0.5 as well (10:05)
-> hardware will do this so hardare takes the z value as -0.5 (10:12) and compare with the(10:21)
value stored in the depth buffer as 1.
-> since value -.5 is closer to the screen than the value 1 so it passed the test and become
pixel (10:40)
->so at the end. It will change the center from value of 000 to 100 with z=-0.5(10:58)(10:10)
->it will apply to all of the fragment with its assocaited depth (11:37)
->let's render the blue triangle (11:58)
->We need to set the color as 001 for RGB (12:21) with depth value 0.5
->We need to write the color buffer as 001 for RGB in color buffer (12:39)
->since the .5 > -0.5 so the fragment can't be dispalyed as pixel (12:54) since it fails
the depth test (13:09) 
*/
