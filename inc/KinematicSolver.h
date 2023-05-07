#pragma once

class kinematicSolver {
private:
    float m_L1;
    float m_L2;
    float m_Px;
    float m_Py;
    float m_Mx;
    float m_My;
    void visualization(float newAlpha, float newBeta) const; 
public:
    kinematicSolver(float L1, float L2, float Mx, float My) {
        m_L1 = L1;
        m_L2 = L2;
        m_Mx = Mx;
        m_My = My;
    }

    void solve();
};