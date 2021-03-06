//
// Created by Tim Schijvenaars on 16-05-16.
//

#include "WiiHandler.h"

#include <stdio.h>                      /* for printf */
#include <thread>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <cstdlib>
#include "wiiuse/src/wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */
#include "Camera.h"



#ifndef WIIUSE_WIN32
#include <unistd.h>                     /* for usleep */
#endif

#define MAX_WIIMOTES				2


/**
 *	@brief Callback that handles an event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *
 *	This function is called automatically by the wiiuse library when an
 *	event occurs on the specified wiimote.
 */



void WiiHandler::handle_event(struct wiimote_t* wm,int i) {
//    Camera* mainCamera = camera;

    //printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

    /* if a button is pressed, report it */
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
        //printf("A pressed\n");
        if(i == 0){
            is_A1 = true;
        }
        if(i == 1){
            is_A2 = true;
        }
    }else
    {
        if(i == 0){
            is_A1 = false;
        }
        if(i == 1){
            is_A2 = false;
        }
    }

    if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
        if(i == 0){
            is_B1 = true;
        }
        if(i == 1){
            is_B2 = true;
        }
    }else
    {
        if(i == 0){
            is_B1 = false;
        }
        if(i == 1){
            is_B2 = false;
        }
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		//printf("UP pressed\n");

        if(i == 0){
            Up1_pressed = true;
        }
        if(i == 1){
            Up2_pressed = true;
        }
	}else
	{
        if(i == 0){
            Up1_pressed = false;
        }
        if(i == 1){
            Up2_pressed = false;
        }
	}
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))	{
       // printf("DOWN pressed\n");
        if(i == 0){
            Down1_pressed = true;
        }
        if(i == 1){
            Down2_pressed = true;
        }
	}else
	{
        if(i == 0){
            Down1_pressed = false;
        }
        if(i == 1){
            Down2_pressed = false;
        }
	}
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
        printf("LEFT pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
        printf("RIGHT pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
        printf("MINUS pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
        printf("PLUS pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
        printf("ONE pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
        printf("TWO pressed\n");
    }
    if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
        printf("HOME pressed\n");
    }

    /*
     *	Pressing minus will tell the wiimote we are no longer interested in movement.
     *	This is useful because it saves battery power.
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) {
        //wiiuse_motion_sensing(wm, 0);
    }

    /*
     *	Pressing plus will tell the wiimote we are interested in movement.
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) {
        /*wiiuse_motion_sensing(wm, 1);*/
		//wiiuse_set_ir(wm, 1);
    }

    /*
     *	Pressing B will toggle the rumble
     *
     *	if B is pressed but is not held, toggle the rumble
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) {
        //wiiuse_toggle_rumble(wm);
    }

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
    }
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
        //wiiuse_set_ir(wm, 0);
    }

    /*
     * Motion+ support
     */
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
        if (WIIUSE_USING_EXP(wm)) {
            //wiiuse_set_motion_plus(wm, 2);    // nunchuck pass-through
        } else {
            //wiiuse_set_motion_plus(wm, 1);    // standalone
        }
    }

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
        //wiiuse_set_motion_plus(wm, 0); // off
    }

    /* if the accelerometer is turned on then print angles */
    if (WIIUSE_USING_ACC(wm)) {
        //printf("wiimote roll  = %f [%f]\n", wm->orient.roll, wm->orient.a_roll);
        //printf("wiimote pitch = %f [%f]\n", wm->orient.pitch, wm->orient.a_pitch);
        //printf("wiimote yaw   = %f\n", wm->orient.yaw);
    }

    /*
     *	If IR tracking is enabled then print the coordinates
     *	on the virtual screen that the wiimote is pointing to.
     *
     *	Also make sure that we see at least 1 dot.
     */
    if (WIIUSE_USING_IR(wm)) {
        int i = 0;

        /* go through each of the 4 possible IR sources */
        for (; i < 4; ++i) {
            /* check if the source is visible */
            if(i == 0) {
                player1X = wm->ir.dot[i].x;
                player1Y = wm->ir.dot[i].y;

//            if (wm->ir.dot[i].visible) {
//                if(i == 0){
//                    this->wiiMoteP1 = wm;
//                }
//                //printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
//                //printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
//                //printf("IR z distance: %f\n", wm->ir.z);
//            }
//            printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
//            printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
//            printf("IR z distance: %f\n", wm->ir.z);
            }
        }



    }

    /* show events specific to supported expansions */
    if (wm->exp.type == EXP_NUNCHUK || wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
        /* nunchuk */
        struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;

        if (IS_PRESSED(nc, NUNCHUK_BUTTON_C)) {
            printf("Nunchuk: C pressed\n");
        }
        if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z)) {
            printf("Nunchuk: Z pressed\n");
        }

        if(i == 0){
            if(abs(nc->js.x * 10) > 1 || abs(nc->js.y * 10) > 1) {
                rot1X -= nc->js.y * 2;
                if (rot1X > 30) {
                    rot1X = 30;
                } else if (rot1X < -30) {
                    rot1X = -30;
                }
                rot1Y += nc->js.x * 2;
            }
        }
        if(i == 1){
            if(abs(nc->js.x * 10) > 1 || abs(nc->js.y * 10) > 1){
                rot2X -= nc->js.y * 2;
                if(rot2X > 30){
                    rot2X = 30;
                }else if(rot2X < -30){
                    rot2X = -30;
                }
                rot2Y += nc->js.x * 2;
            }
        }

//        printf("nunchuk roll  = %f\n", nc->orient.roll);
//        printf("nunchuk pitch = %f\n", nc->orient.pitch);
//        printf("nunchuk yaw   = %f\n", nc->orient.yaw);
//
//        printf("nunchuk joystick angle:     %f\n", nc->js.ang);
//        printf("nunchuk joystick magnitude: %f\n", nc->js.mag);
//
//        printf("nunchuk joystick vals:      %f, %f\n", nc->js.x, nc->js.y);
//        printf("nunchuk joystick calibration (min, center, max): x: %i, %i, %i  y: %i, %i, %i\n",
//               nc->js.min.x,
//               nc->js.center.x,
//               nc->js.max.x,
//               nc->js.min.y,
//               nc->js.center.y,
//               nc->js.max.y);

//        if(abs(nc->js.x * 10) > 1 || abs(nc->js.y * 10) > 1){
//            mainCamera->rotX -= nc->js.y * 2;
//            if(mainCamera->rotX > 30){
//                mainCamera->rotX = 30;
//            }else if(mainCamera->rotX < -30){
//                mainCamera->rotX = -30;
//            }
//            mainCamera->rotY += nc->js.x * 2;
//            glutWarpPointer(mainCamera->width / 2, mainCamera->height / 2);
//        }
    }
    if (wm->exp.type == EXP_MOTION_PLUS ||
        wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
       // printf("Motion+ angular rates (deg/sec): pitch:%03.2f roll:%03.2f yaw:%03.2f\n",
       //        wm->exp.mp.angle_rate_gyro.pitch,
       //        wm->exp.mp.angle_rate_gyro.roll,
       //        wm->exp.mp.angle_rate_gyro.yaw);
    }
}

/**
 *	@brief Callback that handles a controller status event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *	@param attachment		Is there an attachment? (1 for yes, 0 for no)
 *	@param speaker			Is the speaker enabled? (1 for yes, 0 for no)
 *	@param ir				Is the IR support enabled? (1 for yes, 0 for no)
 *	@param led				What LEDs are lit.
 *	@param battery_level	Battery level, between 0.0 (0%) and 1.0 (100%).
 *
 *	This occurs when either the controller status changed
 *	or the controller status was requested explicitly by
 *	wiiuse_status().
 *
 *	One reason the status can change is if the nunchuk was
 *	inserted or removed from the expansion port.
 */
void WiiHandler::handle_ctrl_status(struct wiimote_t* wm) {
    //printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

    //printf("attachment:      %i\n", wm->exp.type);
    //printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
    //printf("ir:              %i\n", WIIUSE_USING_IR(wm));
    //printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
    //printf("battery:         %f %%\n", wm->battery_level);
}



/**
 *	@brief Callback that handles a disconnection event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *
 *	This can happen if the POWER button is pressed, or
 *	if the connection is interrupted.
 */
void WiiHandler::handle_disconnect(wiimote* wm) {
    //printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);

}

short WiiHandler::any_wiimote_connected(wiimote** wm, int wiimotes) {
    int i;
    if (!wm) {
        return 0;
    }

    for (i = 0; i < wiimotes; i++) {
        if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
            return 1;
        }
    }

    return 0;
}


/**
 *	@brief main()
 *
 *	Connect to up to two wiimotes and print any events
 *	that occur on either device.
 */
void WiiHandler::wiiMoteLoop() {
    wiimote** wiimotes;
    int found, connected;

    /*
     *	Initialize an array of wiimote objects.
     *	The parameter is the number of wiimotes I want to create.
     */
    wiimotes =  wiiuse_init(MAX_WIIMOTES);

    /*
     *	Find wiimote devices
     *
     *	Now we need to find some wiimotes.
     *	Give the function the wiimote array we created, and tell it there
     *	are MAX_WIIMOTES wiimotes we are interested in.
     *
     *	Set the timeout to be 5 seconds.
     *
     *	This will return the number of actual wiimotes that are in discovery mode.
     */
    found = wiiuse_find(wiimotes, MAX_WIIMOTES, 8);
    if (!found) {
        printf("No wiimotes found.\n");
        //return 0;
    }
    printf("Wiimotes found");

    /*
     *	Connect to the wiimotes
     *
     *	Now that we found some wiimotes, connect to them.
     *	Give the function the wiimote array and the number
     *	of wiimote devices we found.
     *
     *	This will return the number of established connections to the found wiimotes.
     */
    connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
    if (connected) {
        printf("Connected to %i wiimotes (of %i found).\n", connected, found);


    } else {
        printf("Failed to connect to any wiimote.\n");
        //return 0;
    }
    printf("Wiimotes connected");

    /*
     *	Now set the LEDs and rumble for a second so it's easy
     *	to tell which wiimotes are connected (just like the wii does).
     */
    wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
    wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);

    //wiiuse_rumble(wiimotes[0], 1);
    //wiiuse_rumble(wiimotes[1], 1);

//#ifndef WIIUSE_WIN32
//    usleep(200000);
//#else
//    Sleep(200);
//#endif

    if(wiimotes[0] != 0){
        wiiMoteP1 = wiimotes[0];
    }
    if(wiimotes[1] != 0){
        wiiMoteP2 = wiimotes[1];
    }
    //wiiuse_rumble(wiimotes[0], 0);
    //wiiuse_rumble(wiimotes[1], 0);

    //printf("\nControls:\n");
    //printf("\tB toggles rumble.\n");
    //printf("\t+ to start Wiimote accelerometer reporting, - to stop\n");
    //printf("\tUP to start IR camera (sensor bar mode), DOWN to stop.\n");
    //printf("\t1 to start Motion+ reporting, 2 to stop.\n");
    //printf("\n\n");

    /*
     *	Maybe I'm interested in the battery power of the 0th
     *	wiimote.  This should be WIIMOTE_ID_1 but to be sure
     *	you can get the wiimote associated with WIIMOTE_ID_1
     *	using the wiiuse_get_by_id() function.
     *
     *	A status request will return other things too, like
     *	if any expansions are plugged into the wiimote or
     *	what LEDs are lit.
     */
    /* wiiuse_status(wiimotes[0]); */

    /*
     *	This is the main loop
     *
     *	wiiuse_poll() needs to be called with the wiimote array
     *	and the number of wiimote structures in that array
     *	(it doesn't matter if some of those wiimotes are not used
     *	or are not connected).
     *
     *	This function will set the event flag for each wiimote
     *	when the wiimote has things to report.
     */

    while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
        if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
            /*
             *	This happens if something happened on any wiimote.
             *	So go through each one and check if anything happened.
             */
            int i = 0;
            for (; i < MAX_WIIMOTES; ++i) {
                switch (wiimotes[i]->event) {
                    case WIIUSE_EVENT:
                        /* a generic event occurred */
                            handle_event(wiimotes[i], i);
                        break;

                    case WIIUSE_STATUS:
                        /* a status event occurred */
                        handle_ctrl_status(wiimotes[i]);
                        break;

                    case WIIUSE_DISCONNECT:
                    case WIIUSE_UNEXPECTED_DISCONNECT:
                        /* the wiimote disconnected */
                        handle_disconnect(wiimotes[i]);
                        break;

                    case WIIUSE_READ_DATA:
                        /*
                         *	Data we requested to read was returned.
                         *	Take a look at wiimotes[i]->read_req
                         *	for the data.
                         */
                        break;

                    case WIIUSE_NUNCHUK_INSERTED:
                        /* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
                        /* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
                        printf("Nunchuk inserted.\n");
                        break;
                    case WIIUSE_MOTION_PLUS_ACTIVATED:
                        printf("Motion+ was activated\n");
                        break;

                    case WIIUSE_NUNCHUK_REMOVED:
                    case WIIUSE_MOTION_PLUS_REMOVED:
                        /* some expansion was removed */
                        handle_ctrl_status(wiimotes[i]);
                        printf("An expansion was removed.\n");
                        break;

                    default:
                        break;
                }
            }
        }
    }
    /*
     *	Disconnect the wiimotes
     */
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);

    //return 0;
}