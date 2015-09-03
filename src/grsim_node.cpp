#include "ros/ros.h"
#include "std_msgs/String.h"
#include "grSim_Packet.pb.h"
#include "grSim_Replacement.pb.h"
#include "grSim_Commands.pb.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtNetwork>

#include "krssg_ssl_msgs/gr_BallReplacement.h"
#include "krssg_ssl_msgs/gr_Robot_Command.h"
#include "krssg_ssl_msgs/gr_RobotReplacement.h"
#include "krssg_ssl_msgs/gr_Packet.h"
#include "krssg_ssl_msgs/gr_Commands.h"
#include "krssg_ssl_msgs/gr_Replacement.h"


using namespace std;

QUdpSocket udpsocket;
QHostAddress _addr = QHostAddress("127.0.0.1");
quint16 _port = 20011;

void Callback(const krssg_ssl_msgs::gr_Commands::ConstPtr& msg)
{
		grSim_Packet packet;
		packet.mutable_commands()->set_isteamyellow(msg->isteamyellow);
		packet.mutable_commands()->set_timestamp(msg->timestamp);
		grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
		command->set_id(msg->robot_commands.id);
		command->set_kickspeedx(msg->robot_commands.kickspeedx);
		command->set_kickspeedz(msg->robot_commands.kickspeedz);
		command->set_veltangent(msg->robot_commands.veltangent);
		command->set_velnormal(msg->robot_commands.velnormal);
		command->set_velangular(msg->robot_commands.velangular);
		command->set_spinner(msg->robot_commands.spinner);
		command->set_wheelsspeed(msg->robot_commands.wheelsspeed);
		command->set_wheel1(msg->robot_commands.wheel1);
		command->set_wheel2(msg->robot_commands.wheel2);
		command->set_wheel3(msg->robot_commands.wheel3);
		command->set_wheel4(msg->robot_commands.wheel4);
		QByteArray dgram;
		dgram.resize(packet.ByteSize());
		packet.SerializeToArray(dgram.data(), dgram.size());
		udpsocket.writeDatagram(dgram, _addr, _port);
}

int main(int argc, char **argv)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	ros::init(argc, argv, "grsim_node");
	ros::NodeHandle n,n1;
	ros::Subscriber sub = n1.subscribe("/grsim_data", 1000, Callback);
	ros::spin();
	return 0;
}
