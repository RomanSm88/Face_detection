#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <QtGui>
#include <QTime>
#include "ui_face_detection.h"
#include <opencv2\opencv.hpp>
#include <algorithm>

using namespace cv;

class Face_detection : public QWidget
{
	Q_OBJECT

public:
	Face_detection(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Face_detection();



private:
	Ui::Face_detectionClass ui;
	// Указатель для хранения классификаторов Харра, которые будут загружены из файла
	CascadeClassifier *haar_cascade;
	// Указатель на файл с классификатором
	const char *haarcascade_frontalface_alt2;
	// Указатель на видео-файл
	VideoCapture *file;
	// Создаем контейнер-список для хранения значений цвета рамки.
	QList<CvScalar> colors;
	// Контейнер - вектор, из стандратной библиотеки STL, для хранения координат лица, детектированного на изображении
	vector<Rect> vector_objekt; // Тип вектора определяется, как Rес, т.е - это массив, элементы которого являются матрицами, размерностью 2x2
	// Указатель на объект изображения
	QImage *qimage;
	// Указатель на объект библиотеки Qt для вывода изображения - QPixmap
	QPixmap *qpix;
	double height_pix, width_pix;
	QTimer *time;
	QTimer *fps_time;
	QTime *time_zaderjka;
	string fileName;
	// Суммирование кадров прошедших обработку
	int fps_summ;
	// Число кадров прошедших обработку
	int fps_detect;
	// Метод управления интерфейсными кнопками
	void en_ds_knopci(bool znach);
	// Метод остановки воспроизведения или трансляции видео с камеры
	void stop_video();
	// Ключевой метод обработки изображения
	void face_search(Mat &src, Mat &temp, double =720.0, double =480.0);
	void face_search(Mat &src, double =720.0, double =480.0);
	// Метод проверки открытия видеопотока
	bool proverka_otkrxtiy();
	// Создаем слот для вывода изображения после обработки библиотекой openCV
	private slots:
		void on_actionCapture_opencv();
		void on_actionCapture_opencv_camera();
		void knopka_play();
		void knopka_obzor();
		void fps_count();
		void radio_button_fail();
		void radio_button_camera();
};

#endif // FACE_DETECTION_H
