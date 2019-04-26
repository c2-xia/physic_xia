using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lvDaiController : MonoBehaviour {

    public Transform[] lvDais;
    public Transform    left;
    public Transform    right;
    public Transform    center;
    public float lvDaiHeight = 0.05f;
    public float radius = 0.338f;
    public float speed = 0.01f;
    public float centerY = -0.5f;
    public float RotationOffsetZ = 3.64f;
    public Vector3 upRight = new Vector3(0,0.1f,-1f);
    public Vector3 downRight = new Vector3(0, 0.1f, 1f);
    public float dertaTimeCal = 0.016f;
    void Start () {
        lvDais = new Transform[66];//66
        for (int i = 1; i <= 66; i++)
        {
            string strBoneName = "Bone" + string.Format("{0:D3}", i);
            Transform t = transform.Find(strBoneName);
            lvDais[i - 1] = t;
        }
        //lvDais = new Transform[1];
        //string strBoneName = "Bone" + string.Format("{0:D3}", 2);
        //lvDais[0] = transform.Find(strBoneName);
        lvDaiHeight = 0.05f;
        radius = 0.338f;
        centerY = left.position.y;
        speed = 0.5f; 
    }
	bool FloatApproxmate(float a,float b,float dertaMin)
    {
        return Mathf.Abs(a - b) < dertaMin;
    }
	void Update () {
        //dertaTimeCal = Time.fixedDeltaTime;
        for (int i = 0; i < lvDais.Length; i++)
        { 
            Transform t = lvDais[i];
            //1.位移
            //1.1 方向 left:1,right -1
            bool isRotating = false;
            
            int dir = 0;  
            float dot = Vector3.Dot(t.right, upRight);
            Vector3 p1 = t.position; 
            if (FloatApproxmate(dot,1,0.01f) && right.position.z >= t.position.z)
            {
                if (p1.z > center.position.z && p1.y> center.position.y)
                {
                    Vector3 nowPos = t.position;
                    t.position = new Vector3(nowPos.x, centerY + radius, nowPos.z);
                    t.eulerAngles = new Vector3(0, 90f, 3.64f);
                }                
                dir = 1;
            }
            else if(FloatApproxmate(dot, -1, 0.01f) && left.position.z <= t.position.z)
            {
                if (p1.z < center.position.z && p1.y < center.position.y)
                {
                    t.eulerAngles = new Vector3(0, -90f, 3.64f);
                    Vector3 nowPos = t.position; 
                    t.position = new Vector3(nowPos.x, centerY - radius, nowPos.z);
                    //t.right = new Vector3(0,0.1f,1.0f);
                    float d_angletest = angle_360(t.right, upRight);
                }
                dir = -1;
            }
            else
            {
                isRotating = true;
            }
             
            float distance = 0;
            Vector3 targetPos = Vector3.zero;
            if ( dir == 1 )
            { 
                distance = left.position.z - right.position.z ;
                targetPos = left.position;
            }
            else if( dir == -1 )
            {
                distance = right.position.z - left.position.z;
                targetPos = right.position;
            }
            float d_move = distance * speed * dertaTimeCal;
           
            if (isRotating)
            {
                distance = Mathf.Abs(right.position.z - left.position.z);
                d_move = distance * speed * dertaTimeCal;
                d_move = Mathf.Abs(d_move);
                Vector3 p = t.localPosition;
                if(p.z> center.position.z)
                {
                    //right
                    targetPos = right.position;
                    if (d_move < radius * Mathf.PI)
                    {
                        rotate(d_move, targetPos, t, -1);                       
                    }
                    else
                    {
                        d_move = Mathf.Repeat(d_move, radius * Mathf.PI);
                        t.position = new Vector3(targetPos.x, centerY + radius, targetPos.z);
                        t.eulerAngles = new Vector3(0,90f,3.64f);
                        goLeft(t, targetPos, d_move);
                    }                    
                }
                else
                {
                    //left
                    targetPos = left.position;

                    if (d_move < radius * Mathf.PI)
                    {
                        rotate(d_move, targetPos, t, 1);
                    }
                    else
                    {
                        d_move = Mathf.Repeat(d_move, radius * Mathf.PI);
                        t.position = new Vector3(targetPos.x, centerY - radius, targetPos.z);
                        t.eulerAngles = new Vector3(0, -90f, 3.64f);
                        goRight(t, targetPos, d_move);
                    }
                    
                }
            }            
            else
            {
                if (dir == 1)
                {
                    goLeft(t, targetPos, d_move);

                }
                else
                {
                    goRight(t, targetPos, d_move);
                }
            }
             
            //2.旋转

        }
    }


    void goLeft(Transform t,Vector3 targetPos,float distance)
    { 
        Vector3 nowPos = t.position;
        float d_move = distance ;
        t.position = new Vector3(nowPos.x, nowPos.y, nowPos.z + d_move);
        float d_distance = targetPos.z - t.position.z;
        if (d_distance * -1 < 0)
        {
            if(Mathf.Abs(d_distance) < radius * Mathf.PI)
            {
                rotate(d_distance, targetPos, t,1);
                //UnityEditor.EditorApplication.isPaused = true;
            }
            else
            {
                nowPos = t.position;
                t.position = new Vector3(targetPos.x , centerY - radius, targetPos.z);
                float m_distance = d_distance - radius * Mathf.PI;
                goRight(t,this.right.position, m_distance);
            }
        }
    }

    void goRight(Transform t, Vector3 targetPos, float distance)
    {
        Vector3 nowPos = t.position;
        float d_move = distance;
        t.position = new Vector3(nowPos.x, nowPos.y, nowPos.z + d_move);
        float d_distance = targetPos.z - t.position.z;
        if (d_distance * 1 < 0)
        {
            if (Mathf.Abs(d_distance) < radius * Mathf.PI)
            {
                rotate(d_distance, targetPos, t, -1);
            }
            else
            {
                nowPos = t.position;
                t.position = new Vector3(targetPos.x, centerY + radius, targetPos.z);
                float m_distance = d_distance - radius * Mathf.PI;
                goLeft(t, this.left.position, m_distance);
            }
        }
    }
    float angle_360(Vector3 from_, Vector3 to_)
    {

        Vector3 v3 = Vector3.Cross(from_, to_);

        if (v3.z > 0 )
            return Vector3.Angle(from_, to_);
        else
            return 360 - Vector3.Angle(from_, to_);

    }
    void rotate(float d_distance, Vector3 targetPos, Transform t,int dir)
    {
        float angle = Mathf.Abs(d_distance) / (2 * radius);
        float eulerAngle = angle * Mathf.Rad2Deg *-dir;
        Vector3 euler = t.localEulerAngles;

        float d_angletest = angle_360(t.right, upRight);
        t.localEulerAngles = euler + new Vector3(0, 0, eulerAngle);
        float z_test = t.localEulerAngles.z;
         
        
        float dy = Mathf.Sin(z_test * Mathf.Deg2Rad) * radius ;
        float dx = Mathf.Cos(z_test * Mathf.Deg2Rad) * radius * dir;
        t.position = targetPos + new Vector3(0, dx, dy);

        z_test = t.localEulerAngles.z;
         
         
        float d_angle = angle_360(t.right, upRight);
        float test_v = Mathf.Sin( Mathf.Deg2Rad * d_angle);
        
        //if( Mathf.Repeat( d_angle, 180.0f ) > 90 )
        {
            float y_check = t.position.y - this.centerY;
            if (test_v * dir> 0 &&(y_check* dir)<0)
            {
                z_test += this.RotationOffsetZ;
                z_test = Mathf.Repeat(z_test, 360.0f);
                if (dir == 1)
                {
                    if (z_test > 0 && z_test<180)
                    {
                        z_test = Mathf.Max(z_test, 180.0f);
                        float m_distance = (180.0f - z_test)* Mathf.Deg2Rad * radius* dir;
                        t.eulerAngles = new Vector3(0, -90f, 3.64f); 
                        goRight(t, this.right.position, m_distance); 
                    }
                }
                else if (dir == -1)
                {
                    if (z_test > 180 && z_test < 360)
                        //if (z_test > 0 && z_test < 180)
                    {
                        z_test = Mathf.Repeat(z_test,180.0f);
                        float m_distance = (z_test) * Mathf.Deg2Rad * radius* dir;
                        t.eulerAngles = new Vector3(0, 90f, 3.64f);
                        goLeft(t, this.left.position, m_distance);
                    }
                }
            }
        }
        
    }
}
