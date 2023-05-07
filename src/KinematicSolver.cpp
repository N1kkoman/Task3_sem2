#include <KinematicSolver.h>
#include <iostream>
#include <SFML/Graphics.hpp>

void kinematicSolver::solve() {
        double B = sqrt(pow(m_Mx, 2) + pow(m_My, 2)); // расстояние от начала до заданной точки M

        // Формулы для вычисления углов newAlpha и newBeta основаны на теореме косинусов для треугольников. Углы в радианах.
        auto newAlpha = acos(m_Px / B) - acos((pow(m_L1, 2) - pow(m_L2, 2) + (B * B)) / (2 * B * m_L1));
        auto newBeta = acos(-1) - acos((pow(m_L1, 2) + pow(m_L2, 2) - (B * B)) / (2 * m_L1 * m_L2));

        // если средняя точка P выше Ox берем углы в первом случае, иначе другие
        if (sin(newAlpha) >= 0) {
            m_Px = m_L1 * cos(newAlpha); // координаты средней точки
            m_Py = m_L1 * sin(newAlpha);
        }
        else {
            newAlpha = acos(m_Mx / B) + acos((pow(m_L1, 2) - pow(m_L2, 2) + (B * B)) / (2 * B * m_L1)); // углы во втором случае
            newBeta = -newBeta;
            m_Px = m_L1 * cos(newAlpha); // координаты средней точки
            m_Py = m_L1 * sin(newAlpha);
        }

        newAlpha = static_cast<float>(newAlpha * 180 / acos(-1)); // переводим радианы в градусы
        newBeta = newAlpha + static_cast<float>(newBeta * 180 / acos(-1));
        if (isnan(newAlpha) || isnan(newBeta)) { // если в результате вычислений появилось значение NaN (Not A Number)
            std::cout << "Error in the input data" << std::endl;
            std::exit(0);
        }
            visualization(newAlpha, newBeta);
        
}

void kinematicSolver::visualization(float newAlpha, float newBeta) const {
    std::cout << "Alpha: " << newAlpha << std::endl;
    std::cout << "Beta: " << newBeta << std::endl;
    std::cout << "P: " << m_Px << " " << m_Py << std::endl;
    std::cout << "M: " << m_Mx << " " << m_My << std::endl;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "task3");
    float x = static_cast<float>(window.getSize().x);
    float y = static_cast<float>(window.getSize().y);

    // Искомая точка
    sf::CircleShape M(10);
    M.setPosition((x / 2) + m_Mx - 10, (y / 2) - m_My - 10);
    M.setFillColor(sf::Color::Red);

    // Точка соединения
    sf::CircleShape P(10);
    P.setPosition((x / 2) + m_Px - 10, (y / 2) - m_Py - 10);
    P.setFillColor(sf::Color(255, 160, 00));

    // Точка начала
    sf::CircleShape O(10);
    O.setPosition((x / 2) - 10, (y / 2) - 10);
    O.setFillColor(sf::Color(0, 255, 0));

    // Первое звено
    sf::RectangleShape line1(sf::Vector2f(m_L1, 7));
    line1.setFillColor(sf::Color::Black);
    line1.setRotation(-newAlpha);
    line1.setPosition(x / 2, y / 2);

    // Второе звено
    sf::RectangleShape line2(sf::Vector2f(m_L2, 7));
    line2.setFillColor(sf::Color(140, 140, 140));
    line2.setRotation(-newBeta);
    line2.setPosition((x / 2) + m_Px, (y / 2) - m_Py);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(line1);
        window.draw(line2);
        window.draw(O);
        window.draw(M);
        window.draw(P);

        window.display();
    }
}
