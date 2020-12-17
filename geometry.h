#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const double eps = 1e-7;

double approx(const double& val) {
    double temp = val * 10000000;
    temp = round(temp);
    temp /= 10000000;
    return temp;
}

using std::cin, std::cout, std::vector;
struct Point {
    double x = 0;
    double y = 0;

    Point() = default;
    explicit Point (const std::pair<double, double>& p) {
        x = p.first;
        y = p.second;
    }
    Point (const double& xx, const double& yy) {
        x = xx;
        y = yy;
    }
    Point (Point p, Point pp) {
        x = pp.x - p.x;
        y = pp.y - p.y;
    }
    ~Point() = default;

    friend Point operator+(const Point& a, const Point& b);
    friend Point operator-(const Point& a, const Point& b);
    friend Point operator*(const Point& a, const double& b);
    friend Point operator/(const Point& a, const double& b);
    Point& operator=(const Point& p) = default;
    bool operator==(const Point& a) const {
        bool b1 = fabs(x - a.x) < eps;
        bool b2 = fabs(y - a.y) < eps;
        return b1 && b2;
    }
    bool operator!=(const Point& a) const{
        return !(*this == a);
    }
    Point operator-() const{
        Point copy(-x, -y);
        return copy;
    }
    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) {
        *this += -p;
        return *this;
    }
    Point& operator*=(const double& v) {
        x *= v;
        y *= v;
        return *this;
    }
    Point& operator/=(const double& v) {
        x /= v;
        y /= v;
        return *this;
    }
    double operator*(const Point& a) const{
        return (x * a.y - y * a.x);
    }

    [[nodiscard]] double len() const {
        return sqrt(x * x + y * y);
    }
    [[nodiscard]] Point rotate(const Point& p, const double& angle) const {
        Point ang(cos(angle), sin(angle));
        Point copy = p - *this;
        double k = copy.len();
        if (k < 1e-7)
            return p;
        copy = copy / k;
        Point res(copy.x * ang.x - copy.y * ang.y, copy.x * ang.y + ang.x * copy.y);
        res *= k;
        return (*this + res);
    }
    [[nodiscard]] Point scale(const Point& p, const double& k) const {
        return *this + (p - *this) * k;
    }
    [[nodiscard]] bool onLine(Point p, Point pp) const {
        double d = ((p - *this) * (pp - *this)) / ((p - *this).len() * (pp - *this).len());
        if (fabs(d) > 1e-7)
            return false;
        bool b1 = (p.x - x) * (pp.x - x) < 1e-7;
        bool b2 = (p.y - y) * (pp.y - y) < 1e-7;
        return b1 && b2;
    }
};
Point operator+(const Point& a, const Point& b) {
    Point copy = a;
    copy += b;
    return copy;
}
Point operator-(const Point& a, const Point& b) {
    Point copy = a;
    copy -= b;
    return copy;
}
Point operator*(const Point& a, const double& b) {
    Point copy = a;
    copy *= b;
    return copy;
}
Point operator/(const Point& a, const double& b) {
    Point copy = a;
    copy /= b;
    return copy;
}

double distanse(const Point& a, const Point& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double dist = sqrt(dx * dx + dy * dy);
    return dist;
}

bool polyCmp(const Point& p, const Point& pp) {
    if (fabs(p.x - pp.x) < 1e-7)
        return p.y < pp.y;
    return p.x < pp.x;
}

struct Line {
    double A = 1;
    double B = 1;
    double C = 0;

    Line() = default;
    Line(const Point& a, const Point& b) {
        if (fabs(a.x * b.y - b.x * a.y) < eps) {
            if (fabs(a.x - b.x) < eps) {
                A = 1;
                B = 0;
                C = -a.x;
            } else {
                double k = (a.y - b.y) / (a.x - b.x);
                Line temp(a, k);
                *this = temp;
            }
        } else {
            C = -1;
            double delta0 = a.x * b.y - a.y * b.x;
            double delta2 = a.x - b.x;
            double delta1 = b.y - a.y;
            A = delta1 / delta0;
            B = delta2 / delta0;
        }
    }
    Line(const double& k, const double& b) {
        A = k;
        B = -1;
        C = b;
    }
    Line(const Point& p, const double& k) {
        A = k;
        B = -1;
        C = - A * p.x - B * p.y;
    }
    Line( const double& k, const Point& p) {
        A = k;
        B = -1;
        C = - A * p.x - B * p.y;
    }
    Line(const double& AA, const double& BB, const double& CC) {
        A = AA;
        B = BB;
        C = CC;
    }
    ~Line() = default;

    Line& operator=(const Line& x) = default;
    bool operator==(const Line& l) const {
        bool b1 = fabs(A * l.B - B * l.A) < eps;
        bool b2 = fabs(A * l.C - C * l.A) < eps;
        bool b3 = fabs(B * l.C - C * l.B) < eps;
        return b1 && b2 && b3;
    }
    bool operator!=(const Line& a) const {
        return !(a == *this);
    }
    Point operator^(const Line& l1) const{
        double delta0 = + A * l1.B - B * l1.A;
        double delta1 = - C * l1.B + B * l1.C;
        double delta2 = - A * l1.C + C * l1.A;
        return Point(delta1 / delta0, delta2 / delta0);
    }

    [[nodiscard]] Line perp(const Point& p) const {
        double cc = B * p.x - A * p.y;
        Line copy(-B, A, cc);
        return copy;
    }
    [[nodiscard]] Point reflex(const Point& p) const {
        Line perpendicular = perp(p);
        Point centre = perpendicular ^ (*this);
        return centre.rotate(p, M_PI);
    }
    [[nodiscard]] bool parallel(const Line& another) const {
        double d = A * another.B - B * another.A;
        return fabs(d) < eps;
    }
    [[nodiscard]] double sign(const Point& p) const {
        return A * p.x + B * p.y + C;
    }
    [[nodiscard]] double distance(const Point& p) const {
        return fabs(sign(p)) / sqrt(A * A + B * B);
    }
};

double distance(const Point& a, const Line& l) {
    double num = std::abs(l.A * a.x + l.B * a.y + l.C);
    double den = std::abs(l.A * l.A + l.B * l.B);
    double dist = num / den;
    return dist;
}

struct Shape {
public:
    virtual void scale(const Point& center, const double& coefficient) = 0;
    [[nodiscard]] virtual bool containsPoint(const Point& p) const = 0;
    [[nodiscard]] virtual double perimeter() const = 0;
    [[nodiscard]] virtual double area() const = 0;
    virtual bool operator==(const Shape& another) const = 0;
    bool operator !=(const Shape& another) const {
        return !(*this == another);
    }
    [[nodiscard]] virtual bool isSimilarTo(const Shape& another) const = 0;
    [[nodiscard]] bool isCongruentTo(const Shape& another) const {
        bool b1 = isSimilarTo(another);
        bool b2 = fabs(perimeter() - another.perimeter()) < eps;
        if (b1 && b2)
            return true;
        return false;
    }
    virtual ~Shape() = 0;
};

Shape::~Shape() = default;

struct Ellipse: public Shape {
    Point F1 = {0, 0};
    Point F2 = {0, 0};
    double a = 1;

    Ellipse() = default;
    Ellipse(const Point& f, const Point& g, const double& aa) {
        a = approx(aa / 2);
        F1 = f;
        F2 = g;
    }
    ~Ellipse() override = default;

    bool operator==(const Shape& another) const final {
        try {
            [[maybe_unused]]Ellipse dummy = dynamic_cast<const Ellipse&>(another);
        } catch (...) {
            return false;
        }
        Ellipse el = dynamic_cast<const Ellipse&>(another);
        if (((F1 == el.F1) || (F1 == el.F2)) && ((F2 == el.F1) || (F2 == el.F2)) && (a == el.a)) {
            return true;
        } else {
            return false;
        }
    }
    [[nodiscard]] bool isSimilarTo(const Shape& another) const final {
        try {
            [[maybe_unused]]Ellipse dummy = dynamic_cast<const Ellipse&>(another);
        } catch (...) {
            return false;
        }
        Ellipse el = dynamic_cast<const Ellipse&>(another);
        if (fabs(eccentricity() - el.eccentricity()) > eps)
            return false;
        return true;
    }
    bool operator!=(const Ellipse& el) const {
        return !(el == *this);
    }

    [[nodiscard]] std::pair<Point, Point> focuses() const {
        return {F1, F2};
    }
    [[nodiscard]] Point center() const{
        Point temp;
        temp.x = ((F1.x + F2.x) / 2);
        temp.y = ((F1.y + F2.y) / 2);
        return temp;
    }
    [[nodiscard]] double getB() const{
        double temp = distanse(center(), F1);
        double B = sqrt(a * a - temp * temp);
        return B;
    }
    [[nodiscard]] double eccentricity() const {
        double b = getB();
        double temp = sqrt(a * a - b * b) / a;
        return temp;
    }
    [[nodiscard]] std::pair<Line, Line> directrices() const {
        Point c = center();
        double e = eccentricity();
        Point p1 = c + (F1 - c) * (1 / e / e);
        Point p2 = c - (F1 - c) * (1 / e / e);
        Line dir1 = Line(F2, F1).perp(p1);
        Line dir2 = Line(F2, F1).perp(p2);
        return {dir1, dir2};
    };
    [[nodiscard]] double area() const override {
        return (M_PI * a * getB());
    }
    [[nodiscard]] double perimeter() const override {
        return (4 * a * std::comp_ellint_2(eccentricity()));
    }
    [[nodiscard]] bool containsPoint(const Point& p) const override {
        return (approx(distanse(p, F1) + distanse(p, F2)) <= approx(2 * a));
    }
    void rotate(const Point& center, const double& angle) {
        F1 = F1.rotate(center, angle);
        F2 = F2.rotate(center, angle);
    }
    void reflex(const Point& p) {
        rotate(p, M_PI);
    }
    void scale(const Point& p, const double& k) override {
        F1 = F1.scale(p, k);
        F2 = F2.scale(p, k);
    }
    [[nodiscard]] std::pair<double, double> axis() const {
        double b = getB();
        return { a, b };
    }
};

struct Circle: public Ellipse {
    Circle() = default;
    Circle(const Point& p, const double& r) {
        a = r;
        F1 = F2 = p;
    }
    ~Circle() override = default;

    [[nodiscard]] double radius() const{
        return a;
    }
};

struct Polygon: public Shape {
    std::vector<Point> points;

    Polygon() = default;
    explicit Polygon(const std::vector<Point>& v) {
        points = v;
    }
    Polygon(const std::initializer_list<const Point>& v) {
        points.assign(v.begin(), v.end());
    }
    void recursiveConstruct(const Point& a) {
        points.push_back(a);
    }
    template<typename... Args>
    void recursiveConstruct(const Point& a, Args... args) {
        points.push_back(a);
        recursiveConstruct(args...);
    }
    template<typename... Args>
    explicit Polygon(Args... args) {
        recursiveConstruct(args...);
    }
    ~Polygon() override = default;

    bool operator==(const Shape& another) const final {
        try {
            [[maybe_unused]]Polygon dummy = dynamic_cast<const Polygon&>(another);
        } catch (const std::bad_cast& e) {
            return false;
        }
        Polygon poly = dynamic_cast<const Polygon&>(another);
        std::vector<Point> our_points = points;
        std::vector<Point> their_points = poly.points;
        sort(our_points.begin(), our_points.end(), &polyCmp);
        sort(their_points.begin(), their_points.end(), &polyCmp);
        for (size_t i = 0; i < our_points.size(); ++i) {
            if (fabs(our_points[i].x - their_points[i].x) > eps || fabs(our_points[i].y - their_points[i].y) > eps)
                return false;
        }
        return true;
    }


    [[nodiscard]] int verticesCount() const{
        return points.size();
    }
    [[nodiscard]] std::vector<Point> getVertices() const{
        return points;
    }
    [[nodiscard]] bool isConvex() const{
        double vector_product = (points[1] - points[0]) * (points[points.size() - 1] - points[0]);
        bool sign = (vector_product >= 0);
        for (size_t i = 1; i < points.size() - 1; ++i) {
            vector_product = (points[i + 1] - points[i]) * (points[i - 1] - points[i]);
            if ((vector_product >= 0) != sign) {
                return false;
            }
        }
        vector_product = (points[0] - points[points.size() - 1]) * (points[points.size() - 2] - points[points.size() - 1]);
        if ((vector_product >= 0) != sign) {
            return false;
        }
        return true;
    }
    [[nodiscard]] double area() const override {
        double sum = 0;
        for (size_t i = 1; i < points.size() - 1; ++i) {
            sum += std::abs((points[i] - points[0]) * (points[i + 1] - points[0]));
        }
        sum /= 2;
        return sum;
    }
    [[nodiscard]] double perimeter() const override {
        double sum = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            sum += (points[i] - points[(i + 1) % points.size()]).len();
        }
        return sum;
    }
    Point center() {
        Point res(0, 0);
        for (Point p : points)
            res = res + p;
        res = res / points.size();
        return res;
    }
    void rotate(const Point& p, const double& angle) {
        for (auto & point : points)
            point = p.rotate(point, angle);
    }
    void reflex(const Point& p) {
        rotate(p, M_PI);
    }
    void reflex(const Line& l) {
        for (auto & point : points)
            point = l.reflex(point);
    }
    void scale(const Point& p, const double& k) override {
        for (auto & point : points)
            point = p.scale(point, k);
    }
    [[nodiscard]] bool containsPoint(const Point& p) const override {
        for (size_t i = 0; i < points.size(); ++i) {
            if (p.onLine(points[i], points[(i + 1) % points.size()]))
                return true;
        }
        while (true) {
            auto a_ = static_cast<double>(rand() + 573);
            auto b_ = static_cast<double>(rand() + 573);
            Point inf(p.x + 1e9 * b_, p.y + 1e9 * a_);
            bool correct = true;
            int ans = 0;
            Line l(p, a_ / b_);
            for (auto pp : points) {
                if (pp.onLine(p, inf))
                    correct = false;
            }
            for (size_t i = 0; i < points.size(); ++i) {
                Line l1(points[i], points[(i + 1) % points.size()]);
                if (l.parallel(l1)) {
                    correct = false;
                    break;
                }
                Point o = l ^ l1;
                bool b1 = o.onLine(points[i], points[(i + 1) % points.size()]);
                bool b2 = o.onLine(p, inf);
                ans += b1 && b2;
            }
            if (!correct)
                continue;
            return ans % 2;
        }
    }
    [[nodiscard]] bool isSimilarTo(const Shape& another) const final {
        try {
            [[maybe_unused]]Polygon dummy = dynamic_cast<const Polygon&>(another);
        } catch (...) {
            return false;
        }
        const auto& poly = dynamic_cast<const Polygon&>(another);
        const std::vector<Point>& our_points = points;
        const std::vector<Point>& their_points = poly.points;
        if (our_points.size() != their_points.size())
            return false;
        double k = perimeter() / poly.perimeter();
        size_t n = our_points.size();
        for (size_t s = 0; s < n; ++s) {
            for (int d_ = -1; d_ < 2; d_ += 2) {
                bool maybe = true;
                for (size_t i = 1; i < n; ++i) {
                    size_t j = size_t(2 * int(n) + int(s) + d_ * int(i)) % n;
                    double l1 = (our_points[i] - our_points[0]).len();
                    double l2 = (their_points[j] - their_points[s]).len();
                    if (fabs(l2 * k - l1) > eps)
                        maybe = false;
                }
                if (maybe)
                    return true;
            }
        }
        return false;
    }
};

struct Rectangle: public Polygon {
    Rectangle() = default;
    Rectangle(const Point& p1, const Point& p2, const double& w) {
        points.resize(4);
        points[0] = p1;
        points[2] = p2;
        double angle = atan(1 / w);
        points[1] = p1.rotate(p2, angle);
        points[1] = (points[1] - p1) * cos(angle) + p1;
        points[3] = p2.rotate(p1, angle);
        points[3] = (points[3] - p2) * cos(angle) + p2;
    }

    [[nodiscard]] std::pair<Line, Line> diagonals() const {
        Line d1(points[0], points[2]);
        Line d2(points[1], points[3]);
        return {d1, d2};
    }
};

struct Square: public Rectangle {
    explicit Square(const Rectangle& f): Rectangle(f) {};
    Square(const Point& p1, const Point& p2): Rectangle(p1, p2, 1) {};

    Circle circumscribedCircle() {
        Point c = center();
        Point r = c - points[0];
        return Circle(c, r.len());
    }
    Circle inscribedCircle() {
        Point c = center();
        Point r = c - points[0];
        return Circle(c, r.len() / sqrt(2));
    }
};

struct Triangle: public Polygon {
    explicit Triangle(const std::vector<Point>& p): Polygon(p) {};
    Triangle(const Point& p1, const Point& p2, const Point& p3) {
        points = {p1, p2, p3};
    }
    Point centroid() {
        return center();
    }
    Point orthocenter() {
        Point c1 = points[0] + (points[1] - points[0]) / 2;
        Point c2 = points[0] + (points[2] - points[0]) / 2;
        Line p1 = Line(points[0], points[1]).perp(c1);
        Line p2 = Line(points[0], points[2]).perp(c2);
        Point c = p1 ^ p2;
        return c;
    }
    Circle circumscribedCircle() {
        Point c = orthocenter();
        return Circle(c, (c - points[0]).len());
    }
    Circle inscribedCircle() {
        Point p10 = (points[0] - points[1]);
        p10 = p10 / p10.len();
        Point p11 = (points[2] - points[1]);
        p11 = p11 / p11.len();
        Line l1(points[1], points[1] + p10 + p11);
        Point p20 = (points[0] - points[2]);
        p20 = p20 / p20.len();
        Point p21 = (points[1] - points[2]);
        p21 = p21 / p21.len();
        Line l2(points[2], points[2] + p21 + p20);
        Point c = l1 ^ l2;
        return Circle(c, Line(points[0], points[2]).distance(c));
    }
    Line EulerLine() {
        return Line(centroid(), orthocenter());
    }
    Circle ninePointsCircle() {
        Triangle temp(points);
        return temp.circumscribedCircle();
    }
};
