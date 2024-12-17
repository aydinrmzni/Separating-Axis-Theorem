#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

// Function to calculate the dot product of two vectors
static float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

// Function to normalize a vector
static sf::Vector2f normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    return v / length;
}

// Function to get the vertices of a rotated rectangle
static std::vector<sf::Vector2f> getVertices(const sf::RectangleShape& rect)
{
    std::vector<sf::Vector2f> vertices;
    const sf::Transform& transform = rect.getTransform();
    sf::FloatRect bounds = rect.getLocalBounds();

    vertices.push_back(transform.transformPoint(bounds.left, bounds.top));
    vertices.push_back(transform.transformPoint(bounds.left + bounds.width, bounds.top));
    vertices.push_back(transform.transformPoint(bounds.left + bounds.width, bounds.top + bounds.height));
    vertices.push_back(transform.transformPoint(bounds.left, bounds.top + bounds.height));

    return vertices;
}

// Function to get the edges of a polygon
static std::vector<sf::Vector2f> getEdges(const std::vector<sf::Vector2f>& vertices)
{
    std::vector<sf::Vector2f> edges;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        sf::Vector2f edge = vertices[(i + 1) % vertices.size()] - vertices[i];
        edges.push_back(edge);
    }
    return edges;
}

// Function to project a polygon onto an axis and get the minimum and maximum values
static void projectOntoAxis(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis, float& min, float& max)
{
    min = max = dotProduct(vertices[0], axis);
    for (size_t i = 1; i < vertices.size(); ++i)
    {
        float projection = dotProduct(vertices[i], axis);
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}

// SAT collision detection between two convex polygons
static bool checkSATCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB)
{
    auto verticesA = getVertices(rectA);
    auto verticesB = getVertices(rectB);

    auto edgesA = getEdges(verticesA);
    auto edgesB = getEdges(verticesB);

    // Combine all axes (perpendicular to edges)
    std::vector<sf::Vector2f> axes;
    for (const auto& edge : edgesA)
    {
        axes.push_back(normalize(sf::Vector2f(-edge.y, edge.x))); // Perpendicular axis
    }
    for (const auto& edge : edgesB)
    {
        axes.push_back(normalize(sf::Vector2f(-edge.y, edge.x))); // Perpendicular axis
    }

    // Test all axes
    for (const auto& axis : axes)
    {
        float minA, maxA, minB, maxB;
        projectOntoAxis(verticesA, axis, minA, maxA);
        projectOntoAxis(verticesB, axis, minB, maxB);

        if (maxA < minB || maxB < minA)
        {
            return false; // No collision if there's a gap
        }
    }

    return true; // Collision detected
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rotating Rectangles with SAT Collision");
    window.setFramerateLimit(60);

    // Create two rectangles
    sf::RectangleShape rectA(sf::Vector2f(150.f, 100.f));
    rectA.setFillColor(sf::Color::Transparent);
    rectA.setOutlineThickness(2.f);
    rectA.setOutlineColor(sf::Color::Green);
    rectA.setOrigin(rectA.getSize().x / 2, rectA.getSize().y / 2);
    rectA.setPosition(300.f, 300.f);

    sf::RectangleShape rectB(sf::Vector2f(120.f, 200.f));
    rectB.setFillColor(sf::Color::Transparent);
    rectB.setOutlineThickness(2.f);
    rectB.setOutlineColor(sf::Color::Green);
    rectB.setOrigin(rectB.getSize().x / 2, rectB.getSize().y / 2);
    rectB.setPosition(500.f, 300.f);

    float rotationSpeedA = 30.f; // Degrees per second
    float rotationSpeedB = -45.f; // Degrees per second

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update rotations
        float deltaTime = clock.restart().asSeconds();
        rectA.rotate(rotationSpeedA * deltaTime);
        rectB.rotate(rotationSpeedB * deltaTime);

        // Check for collision
        if (checkSATCollision(rectA, rectB))
        {
            rectA.setOutlineColor(sf::Color::Red);
            rectB.setOutlineColor(sf::Color::Red);
        } else
        {
            rectA.setOutlineColor(sf::Color::Green);
            rectB.setOutlineColor(sf::Color::Green);
        }

        // Render
        window.clear();
        window.draw(rectA);
        window.draw(rectB);
        window.display();
    }

    return 0;
}
