
#ifndef VROBOT_HEADER_H
#define VROBOT_HEADER_H

#include <string>

struct AxisAngle {
 protected:
  double m_Value = 0;

 public:
  virtual double GetValue() { return m_Value; }

  virtual double SetValue(double value) { m_Value = value; }
};

struct vRobotParams {
 public:
  std::string SDF;
  double X, Y, Z;
};

class CvRobot {
 public:
  virtual void SetAxisAngle(AxisAngle value, std::string AxisID) = 0;
  virtual AxisAngle GetAxisAngle(std::string AxisID) = 0;
  virtual bool IsStable() = 0;
  virtual void Init() = 0;
  virtual std::string GetID() = 0;
  virtual void SetContactTracing(bool value) = 0;
  virtual void SetCollisionToExcept(std::string Name) = 0;
  virtual ~CvRobot(){};
};

#endif /* VROBOT_HEADER_H */
