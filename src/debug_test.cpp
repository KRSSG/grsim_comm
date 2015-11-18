#include "ros/ros.h"
#include "std_msgs/String.h"
#include "grSim_Packet.pb.h"
#include "grSim_Replacement.pb.h"
#include "grSim_Commands.pb.h"
#include <sslDebug_Data.pb.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtNetwork>


using namespace std;

QUdpSocket udpsocket;
QHostAddress _addr = QHostAddress("127.0.0.1");
quint16 _port = 20011;


int main(int argc, char **argv)
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  ros::init(argc, argv, "grsim_node");
  ros::NodeHandle n,n1;
  // ros::Subscriber sub = n1.subscribe("/grsim_data", 1000, Callback);
  ros::Rate loop_rate(10);
  while (ros::ok()) {
    grSim_Packet packet;
    packet.mutable_debuginfo()->set_id(ros::this_node::getName());
    Debug_Circle *circle = packet.mutable_debuginfo()->add_circle();
    Debug_Line *line = packet.mutable_debuginfo()->add_line();
    circle->set_x(0);
    circle->set_y(0);
    circle->set_radius(100.);
    circle->set_color(0);

    line->set_x1(-1000);
    line->set_y1(0);
    line->set_x2(1000);
    line->set_y2(0);
    line->set_color(0);
    QByteArray dgram;
    dgram.resize(packet.ByteSize());
    packet.SerializeToArray(dgram.data(), dgram.size());
    udpsocket.writeDatagram(dgram, _addr, _port);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
