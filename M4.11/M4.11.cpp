#include <iostream>
#include <vector>

class Vehicle {
public:
    virtual void print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
        v.print(os);
        return os;
    }
};

class WaterVehicle : public Vehicle {
private:
    float draft;
public:
    WaterVehicle(float d) : draft(d) {}
    void print(std::ostream& os) const override {
        os << "WaterVehicle Draft: " << draft;
    }
};

class RoadVehicle : public Vehicle {
protected:
    float groundClearance;
public:
    RoadVehicle(float gc) : groundClearance(gc) {}
};

class Wheel {
private:
    float diameter;
public:
    Wheel(float d) : diameter(d) {}
    float getDiameter() const { return diameter; }
};

class Engine {
private:
    float power;
public:
    Engine(float p) : power(p) {}
    float getPower() const { return power; }
};

class Car : public RoadVehicle {
private:
    Wheel frontLeft, frontRight, rearLeft, rearRight;
    //Engine engine;
public:
    Engine engine;
    Car(const Engine& e, const Wheel& fl, const Wheel& fr, const Wheel& rl, const Wheel& rr, float gc)
        : RoadVehicle(gc), engine(e), frontLeft(fl), frontRight(fr), rearLeft(rl), rearRight(rr) {}
    void print(std::ostream& os) const override {
        os << "Car Engine: " << engine.getPower() << " Wheels: "
            << frontLeft.getDiameter() << " " << frontRight.getDiameter()
            << " " << rearLeft.getDiameter() << " " << rearRight.getDiameter()
            << " Ride height: " << groundClearance;
    }
};

class Bicycle : public RoadVehicle {
private:
    Wheel frontWheel, rearWheel;
public:
    Bicycle(const Wheel& fw, const Wheel& rw, float gc)
        : RoadVehicle(gc), frontWheel(fw), rearWheel(rw) {}
    void print(std::ostream& os) const override {
        os << "Bicycle Wheels: " << frontWheel.getDiameter() << " "
            << rearWheel.getDiameter() << " Ride height: " << groundClearance;
    }
};

//class Point {
//private:
//    float x, y, z;
//public:
//    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
//};
//
//class Circle {
//private:
//    const Point center;
//    float radius;
//public:
//    Circle(const Point& c, float r) : center(c), radius(r) {}
//};

float getHighestPower(const std::vector<Vehicle*>& v) {
    float maxPower = 0.0f;
    for (const auto& vehicle : v) {
        Car* car = dynamic_cast<Car*>(vehicle);
        if (car && car->engine.getPower() > maxPower) {
            maxPower = car->engine.getPower();
        }
    }
    return maxPower;
}

int main()
{
    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    //v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    for (const auto& vehicle : v) {
        std::cout << *vehicle << '\n';
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n';

    for (auto& vehicle : v) {
        delete vehicle;
        vehicle = nullptr;
    }

    return 0;
}