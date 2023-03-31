#include "registrationform.h"
#include "ui_registrationform.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    connect(ui->pushButton_accept, SIGNAL(clicked()), SLOT(saveInfo()));
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::saveInfo()
{
    QString mUsername = ui->lineEdit_nickname->text();
    int mAge = ui->lineEdit_age->text().toInt();
    QString mPass = ui->lineEdit_pass->text();

    if(mUsername.isEmpty() || ui->lineEdit_age->text().isEmpty() || mPass.isEmpty() || ui->lineEdit_confirm_pass->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!", "One of the field is empty!");
        return;
    }
    if(mPass != ui->lineEdit_confirm_pass->text())
    {
        QMessageBox::warning(this, "Error!", "Your password is not confirmed!");
        return;
    }
    DBExporter exporter;
    bool result = exporter.exportInfo(mUsername, mPass, mAge);
    if (result)
        QMessageBox::information(this,"Success!","You were registered!");
    else
        QMessageBox::warning(this, "Report", "This login is already taken");

   // PersonClass *newPerson = new PersonClass(mUsername,mPass, mAge);
    //std::shared_ptr<PersonClass> newUser = std::make_shared<PersonClass>(mUsername,mPass,mAge);

}
