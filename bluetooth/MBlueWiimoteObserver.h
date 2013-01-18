/*
 * MBlueMouseObserver.h
 *
 *  Created on: 12.12.2010
 *      Author: Juhana Paavola <juhana.paavola@gmail.com>
 */

#ifndef MBLUEWIIMOTEOBSERVER_H_
#define MBLUEWIIMOTEOBSERVER_H_

#include <bttypes.h>
#include <QByteArray>

class MBlueWiimoteObserver
    {
public:
    virtual void Connected() = 0;
    
    virtual void Disconnected() = 0;

    virtual void Sending() = 0;
    virtual void Receiving(QByteArray buffer) = 0;

   // virtual void AccelerometerDataReady(TInt aX, TInt aY) = 0;
    
    virtual void DeviceSelected(TBTDevAddr aAddr) = 0;
    
    virtual void PowerState(TBool aOn) = 0;
       
    };

#endif /* MBLUEWIIMOTEOBSERVER_H_ */
