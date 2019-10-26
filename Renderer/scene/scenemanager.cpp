#include "scenemanager.h"

SceneManager::SceneManager()
{
}

SceneManager::SceneManager(QImage *frame, const int &screen_width, const int &screen_height)
{
    render_manager = RenderManager(frame, screen_width, screen_height);
}

void SceneManager::render()
{
    Matrix<double> Mpersp = camera_manager.getLookAt() * camera_manager.getProjection();
    for (int i = 0; i < model_manager.countModels(); i++)
    {
        Cube model = model_manager.getModel(i);
        Matrix<double> Mmod = model_manager.getModelView(i) * Mpersp;
        if (model.isOpaque())
        {
            std::vector<Point<3, double>> triangle(3);
            for (int j = 0; j < model.countTriangles(); j++)
            {
                model.getTriangle(triangle, j);
                render_manager.renderTriangle(triangle, Mmod);
            }
        }
    }
}

