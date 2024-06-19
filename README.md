# Computer-Graphics-Projects

**Description**: Projects about computer graphics include upsampling, rasterizing, and geometric modeling techniques (Bezier curves and surfaces using de Casteljau algorithm).

### Contents
- [Rasterizer](https://github.com/JC01111/Computer-Graphics-Projects/blob/55a2446c596cd7c4a798589a069dc501ba5a2b0a/Rasterizer/README.md)
- [Geometric Modeling](https://cal-cs184-student.github.io/hw2-meshedit-sp24-j-c-1/)

### Configuration
Look at this [Tutorial](https://www.youtube.com/watch?v=9EADCyN_Fek) if you want to skip reading or you have any problems with setting up.

1. Make sure that the latest Xcode.app is installed through the Mac app store
2. Clone your assignment repository from GitHub (ssh is recommended)
3. Open your Terminal and use `cd` to change directory into the homework folder
4. Create a folder called `xcode`, and CD into it: `mkdir xcode; cd xcode`  <br> (Remember to delete or replace the original `xcode` folder)
5. Setup cmake for XCode (while inside the `xcode` folder): `cmake -G Xcode ..`
6. Open `Finder` and navigate to the `xcode` folder
7. Double-click on the `<Project Name>.xcodeproj` file to open the project in XCode (it has a blue icon with a pen and paintbrush)
8. Build the project by clicking `Product > Build` on the top bar of your screen
9. Click on `ALL_BUILD`, located near the top right of Xcode
10. Click `Edit Scheme`
11. Select `Run` on the sidebar
12. Select `Info` on the top bar of the `Run` page
13. Set `Executable` to the executable (in the case of Basics, it is `quad_test`)
14. Select `Arguments` (inside `Edit Scheme > Run`) to specify arguments (not necessary for Basics)
15. Select `Options` (inside `Edit Scheme > Run`) and specify the working directory to be the xcode folder.
16. Press the play button to compile and launch the program

#### Common error:
- If the C/C++ compiler can't be found when running cmake (step 5 above), try specifying the compiler with environment variables: `CC=gcc CXX=g++ cmake -G Xcode ..`
