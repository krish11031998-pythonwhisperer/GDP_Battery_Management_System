# Battery Management System for Electrical Motorbike
Worked on a group design project to design and develop a battery management system for Li-ion batteries , as the control system designer and lead programmer. I was responsible of designing and developing a hybrid control and condition monitoring system that comprised of Arduino and Raspberry Pi for sensor measurements , mechanical actuation and data analysis.

### Raspberry Pi
    * Estimation of State-ofCharge (SoC) and State-ofHealth (SoH) of the batteries.
    * Execution of computational algorithms like linear interpolation, etc.
    * Creation and updating CSV files to perform Google Drive upload for user’s access to data for analysis.
    * Transmission important data to Arduino 2 for displaying dashboard.
### Arduino
    *  Measure the Voltages of the batteries.
    * Measure the discharge current of the batteries.
    * Measure the batteries’ temperatures during operation.
    * Measure the acceleration of the batteries.
    * Transmission to the data to Raspberry Pi for further computation.
    * Receiving data from Raspberry Pi and display onto the 4dSystems display.
    * Reporting back the monitoring system via Raspberry Pi at the end of the operation cycle by registering the user’s switch click on the screen. 


![Check out the final group video](https://www.youtube.com/watch?v=v9mOU1CrWdg&feature=youtu.be)
<img width="378" alt="Screen_Shot_2019-10-17_at_7 52 38_PM" src="https://user-images.githubusercontent.com/56647167/68282222-b3ccf380-0092-11ea-89eb-2e42fbc8f68f.png">


