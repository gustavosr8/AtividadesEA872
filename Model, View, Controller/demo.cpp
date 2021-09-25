#include <memory>
#include <iostream>

class Model
{
  private:
    float data;

public:
    Model();
    void set_data(float new_data);
    float get_data();
};

Model::Model() { data=0; std::cout<< "Model Constructor" << std::endl;}
void Model::set_data(float new_data) { data = new_data; }
float Model::get_data() { return data; }

class View
{
  public:
    View();
    void render(int data);
};

View::View() { std::cout << "View Constructor" << std::endl; }
void View::render(int data) {
  std::cout << "Render: " << data << std::endl;
}

class Controller
{
  private:
    std::shared_ptr<Model> const model;
    std::shared_ptr<View> const view;

  public:
    Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view);
    void update();
};

Controller::Controller(std::shared_ptr<Model> model,
    std::shared_ptr<View> view) :
  // Lista de inicialiacao (initialization list)
  model(model),
  view(view)
{
  std::cout << "Controller Constructor" << std::endl;
}

void Controller::update() {
  model->set_data(model->get_data() + 1);
  view->render((int)model->get_data());
}

int main()
{
  std::shared_ptr<Model> model (new Model);
  std::shared_ptr<View> view (new View);
  std::unique_ptr<Controller> controller (new Controller(model, view));
  for (int i=0; i<5; i++)
    controller->update();
  return 0;
}