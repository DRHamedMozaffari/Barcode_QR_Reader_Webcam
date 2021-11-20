# Barcode_QR_Reader_Webcam

Using OpenCV 4 and Zbar libraries, I could write a sample code to decode QR and Barcodes using Webcam. 
I used x64 version of Zbar from Github here: https://github.com/dani4/ZBarWin64 

The code shows frames from webcam and after finding the barcode, it shows type and data contains in the image, wait for getting a key. If you press Esc, it will be closed, 
and if you press del button, it will continue for finding another QR code. The code is general, and it can decode any types of barcode. It is possible to modify the barcode 
type in set_config method of scanner in the file.

How it works, the main method of image processing is not so complicated, but I think it is a properietry code that we can't figure it out easily. 
Frame recorded from webcam --> converted to grayscale --> look for keypoint of the frame --> if find any symbol then read all the symbol --> draw square around the QR code 
--> visualize the QR code --> write the type and content of the QR code 

I hope that this simple example be useful for you
There is Python version of Zbar as well as other versions even for working on iphone and android. 

See here for more information:

http://zbar.sourceforge.net/

https://en.wikipedia.org/wiki/ZBar

https://pypi.org/project/pyzbar/

https://linuxtv.org/downloads/zbar/

https://sourceforge.net/projects/zbar/files/zbar/


