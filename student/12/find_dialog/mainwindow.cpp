#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileLineEdit_editingFinished()
{

    file_ = ui->fileLineEdit->text();

}


void MainWindow::on_keyLineEdit_editingFinished()
{

    key_ = ui->keyLineEdit->text();

}


void MainWindow::on_findPushButton_clicked()
{

    std::ifstream reader(file_.toStdString());
    std::string key_as_string = key_.toStdString();

    ui->textBrowser->clear();

    if(reader) {

        std::string line;
        bool empty = true;
        bool found = false;

        while(getline(reader, line)) {

            empty = false;

            if (!ui->matchCheckBox->isChecked()) {
                std::transform(line.begin(), line.end(), line.begin(),
                    [](unsigned char c){ return std::tolower(c); });
                std::transform(key_as_string.begin(), key_as_string.end(), key_as_string.begin(),
                    [](unsigned char c){ return std::tolower(c); });
            }

            std::string buf;                 // Have a buffer string
            std::stringstream ss(line);       // Insert the string into a stream

            std::vector<std::string> tokens; // Create vector to hold our words

            while (ss >> buf)
                tokens.push_back(buf);

            for (std::string s : tokens) {
                if (s == key_as_string) {
                    ui->textBrowser->append("Word found");
                    found = true;
                    goto exit;
                }
            }

        }

        exit:

        if (empty) {
            ui->textBrowser->append("File found");
        }

        if (!found) {
            ui->textBrowser->append("Word not found");
        }

    } else {
        ui->textBrowser->append("File not found");
    }

}

