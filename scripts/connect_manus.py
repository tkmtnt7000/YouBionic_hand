#! /usr/bin/env/python

import rospy
from std_msgs.msg import Int16
from std_msgs.msg import Header
from sensor_msgs.msg import JointState


def callback(msg):
    rospy.loginfo("done!")
    manus_pub(msg)

def manus_sub():
    rospy.init_node('manus_connector', anonymous=True)
    rospy.Subscriber("/manus/right_hand/joint_states", JointState, callback)
    rospy.spin()
    
def manus_pub(msg):
    pub_deg = rospy.Publisher('right_hand/joint_state', JointState, queue_size=10)
    #pub = rospy.Publisher('right_hand/finger_degree', Int16, queue_size=10)
    joint_state = JointState()
    joint_state.header = Header()
    joint_state.header.stamp = rospy.Time.now()
    joint_state.name = ['thumb', 'index', 'middle', 'ring', 'pinky']
    joint_state.position = [msg.position[3], msg.position[7], msg.position[11], msg.position[15], msg.position[19]]
    #joint_state.position[0] = msg.position[0]
    #joint_state.position[1] = msg.position[4]
    #for i in range(0,5):
        #joint_state.position[i]=msg.position[i*4]
    pub_deg.publish(joint_state)

if __name__ == '__main__':
    manus_sub()
