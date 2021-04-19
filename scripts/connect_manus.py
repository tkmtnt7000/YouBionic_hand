#! /usr/bin/env/python

import rospy
from std_msgs.msg import Int16
from std_msgs.msg import Header
from sensor_msgs.msg import JointState


def callback(msg):
    rospy.loginfo("done!")
    manus_thumb_pub(msg)
    manus_index_pub(msg)
    manus_middle_pub(msg)
    manus_ring_pub(msg)
    manus_pinky_pub(msg)

def manus_sub():
    rospy.init_node('manus_connector', anonymous=True)
    rospy.Subscriber("/manus/right_hand/joint_states", JointState, callback)
    rospy.spin()

def calc_normalize(n):
    return n*13//9 + 30

def manus_thumb_pub(msg):
    pub_thumb = rospy.Publisher('right_hand/thumb', Int16, queue_size=10)
    thumb_deg = Int16()
    thumb_deg.data = msg.position[3]*13//9 + 30
    pub_thumb.publish(thumb_deg)

def manus_index_pub(msg):
    pub_index = rospy.Publisher('right_hand/index', Int16, queue_size=10)
    index_deg = Int16()
    index_deg.data = msg.position[7]*13//9 + 30
    pub_index.publish(index_deg)
    
def manus_middle_pub(msg):
    pub_middle = rospy.Publisher('right_hand/middle', Int16, queue_size=10)
    middle_deg = Int16()
    middle_deg.data = msg.position[3]*13//9 + 30
    pub_middle.publish(middle_deg)
    
def manus_ring_pub(msg):
    pub_ring = rospy.Publisher('right_hand/ring', Int16, queue_size=10)
    ring_deg = Int16()
    ring_deg.data = msg.position[3]*13//9 + 30
    print "ring!"
    pub_ring.publish(ring_deg)

def manus_pinky_pub(msg):
    pub_pinky = rospy.Publisher('right_hand/pinky', Int16, queue_size=10)
    pinky_deg = Int16()
    pinky_deg.data = msg.position[3]*13//9 + 30
    pub_pinky.publish(pinky_deg)
    
def manus_pub(msg):
    pub_deg = rospy.Publisher('right_hand/joint_state', JointState, queue_size=10)
    #pub = rospy.Publisher('right_hand/finger_degree', Int16, queue_size=10)
    joint_state = JointState()
    joint_state.header = Header()
    joint_state.header.stamp = rospy.Time.now()
    joint_state.name = ['thumb', 'index', 'middle', 'ring', 'pinky']
    norm_jointstates = map(calc_normalize, msg.position)
    joint_state.position = [norm_jointstates[3], norm_jointstates[7], norm_jointstates[11], norm_jointstates[15], norm_jointstates[19]]
    #joint_state.position[0] = msg.position[0]
    #joint_state.position[1] = msg.position[4]
    #for i in range(0,5):
        #joint_state.position[i]=msg.position[i*4]
    pub_deg.publish(joint_state)

if __name__ == '__main__':
    manus_sub()
