#include "face_detection.h"

Face_detection::Face_detection(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), haarcascade_frontalface_alt2("./Haar/haarcascade_frontalface_alt2.xml"),
	file(0), time(0), height_pix(0.0), width_pix(0.0), fps_detect(0), fps_time(0), fps_summ(0)
{
	// Устанавливаем параметры окна для созданного объекта
		ui.setupUi(this);
	
	// Загружаем каскад Харра из файла
		haar_cascade = new CascadeClassifier(haarcascade_frontalface_alt2);
	

	// Заполняем контейнер значениями цвета рамки
		colors << cvScalar(0.0,0.0,255.0) << cvScalar(0.0, 128.0, 255.0)
			<< cvScalar(0.0,255.0,255.0) << cvScalar(0.0,255.0,0.0)
			<< cvScalar(255.0,128.0,0.0) << cvScalar(255.0,255.0,0.0)
			<< cvScalar(255.0,0.0,0.0) << cvScalar(255.0,0.0,255.0);
	
	// Создаем объект для вывода обработанного изображения в главное окно программы
		qpix = new QPixmap();
	
	// Создаем высокоточный таймер
		time_zaderjka = new QTime();
	// Элементы управления: QRadioButton
	// Запуск обработчика по умолчанию
		ui.radioButton_2->setChecked(true); // По умолчанию в качестве источника задан файл

	// Вызов обработчкиков при изменении состоянии радиокнопок
		connect(ui.radioButton, SIGNAL(pressed()), this, SLOT(radio_button_camera()));
		connect(ui.radioButton_2, SIGNAL(pressed()), this, SLOT(radio_button_fail()));
	

	// Вызов обработчиков при работе с файлом
	// Вызов обработчика при нажатии на кнопку - "Обзор"
		connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(knopka_obzor()));
	// Вызов обработчика при запуске воспроизведения
		connect(ui.knopka, SIGNAL(clicked()), this, SLOT(knopka_play()));

	
}

void Face_detection::stop_video()
{
	// Сбрасываем счетчик кадров
		fps_detect = 0;

		if (time)
			time->stop();
		if (fps_time)
			fps_time->stop();

		if (file)
			file->~VideoCapture();

	// Обнуляем все значения в элементаx управления
		ui.lineEdit->clear();
		ui.label->clear();
		ui.SizeVideo_1->clear();
		ui.Size_Video_2->clear();
		ui.FPS_1->clear();
		ui.FPS_2->clear();
		ui.label_7->clear();
		ui.label_9->clear();
}

void Face_detection::en_ds_knopci(bool znach)
{
	
		ui.knopka->setEnabled(znach);
		ui.lineEdit->clear();
		ui.lineEdit->setEnabled(znach);
		ui.toolButton->setEnabled(znach);
		ui.label_2->setEnabled(znach);
		ui.label_3->setEnabled(znach);
		ui.label_8->setEnabled(znach);
		ui.checkBox_2->setEnabled(znach);
}

void Face_detection::knopka_play()
{
	// Проверяем была ли выделена память под файл и был ли запушен таймер, если оба параметра истены, производим их сброс
	if (file && time)
	{
		// Останавливаем таймер
		time->stop();
		fps_time->stop();
		// Вызываем диструктор класса VideoCapture и освобождаем память
		file->~VideoCapture();
	}
	// Загружаем файл с видео
		file = new VideoCapture(fileName);

	// Проверка, удалось ли открыть поток
		if (!proverka_otkrxtiy())
			return;


	// Определение свойств видео: частота кадров, разрешение.
	// При необходимости изменяем свойство видео - уменьшение разрешение, для того чтобы снизить время на обработку и подогнать 
	// обработанные кадры к размеру главного окна программы

	if (file->get(CV_CAP_PROP_FRAME_WIDTH) != 720 && file->get(CV_CAP_PROP_FRAME_HEIGHT) != 480)
	{
		ui.label_7->clear();
		ui.label_9->clear();
	// Код для отображения в свойствах
		ui.SizeVideo_1->setText(QString::number(file->get(CV_CAP_PROP_FRAME_WIDTH)) + "x" + QString::number(file->get(CV_CAP_PROP_FRAME_HEIGHT))+ "p"); // Разрешение
	// Частота кадров
		ui.FPS_1->setText(QString::number(file->get(CV_CAP_PROP_FPS))+"k/s"); 
		// Изменяем свойсва видео на стандартные для SD 720x480
		// Сохраняем значения разрешения SD в глобальных переменныx для дальнейшей обработки
		width_pix = 720;
		height_pix = 480;
		// Отображаем измененное разрешение в свойствах
		ui.Size_Video_2->setText(QString::number(width_pix) + "x" + QString::number(height_pix) + "p");
	} else
	{
		// Код для отображения в свойствах
		ui.SizeVideo_1->setText(QString::number(file->get(CV_CAP_PROP_FRAME_WIDTH)) + "x" + QString::number(file->get(CV_CAP_PROP_FRAME_HEIGHT))+ "p"); // Разрешение
		ui.FPS_1->setText(QString::number(file->get(CV_CAP_PROP_FPS))); // Частота кадров

		// Сохраняем значения разрешения в глобальные переменные для дальнейшей обработки
		width_pix = file->get(CV_CAP_PROP_FRAME_WIDTH);
		height_pix = file->get(CV_CAP_PROP_FRAME_HEIGHT);

		// Отображаем измененное разрешение в свойствах
		ui.Size_Video_2->setText(QString::number(width_pix) + "x" + QString::number(height_pix));
	}


	// Устанавливаем таймер - задержка вывода
		time = new QTimer(this);
	// Устанавливаем таймер для вычисления частоты кадров
		fps_time = new QTimer(this); 
		connect(fps_time, SIGNAL(timeout()), this, SLOT(fps_count()));  // Соединением таймер со слотом, каждые 1000мс = 1с в процессе работы программы
		fps_time->start(1000); 
	// Соединение сигнала и слота
	// При нажатии на кнопку начинается воспросизведение
		connect (time, SIGNAL(timeout()), this, SLOT(on_actionCapture_opencv()));
	// Устанавливаем временную задержку вызова метода on_actionCapture_opencv()
	// Временная задарежка определяется по формуле: отношение 1секунды, выраженной в милесекундах = 1000мс, к частоте обрабатываемого видео (FPS)
		time->start(1000/file->get(CV_CAP_PROP_FPS));
	
	// Запускаем таймер для замера времени выполнения обработки
		time_zaderjka->restart();
	
}
// Не оптимизированный алгоритм
void Face_detection::face_search(cv::Mat &src, double width, double height)
{
	QImage qmag;

	// Формируем  разрешения кадра из переменных width_pix, height_pix
	cv::resize(src, src, Size(width,height), INTER_LINEAR);


	// Запускаем основной алгоритм поиска, если чек-бокс включен
	if (ui.checkBox->isChecked())
	{

		haar_cascade->detectMultiScale(
			src, // Источник
			vector_objekt,  // Приемник, будет сохранено не изображение а координаты искомого объекта
			1.3, // Коофициент увеличения масшатаба
			3, // Минимальное число соседних областенй, значение которых будет учитывать в принятии решения: это лицо или нет?
			CV_HAAR_DO_CANNY_PRUNING, // Константа, позволяет пропускать области на изображении, в которых лица не может быть ни при каких обстоятельствах.
			Size(30,30) // Размер "скользяшего окна", при перемешении которго осушествляется анализ изображения.
			);

		// контейнер с координатами обрабатывается в цикле.
		for (int i = 0; i < vector_objekt.size(); i++)
		{
			rectangle(src, vector_objekt[i], Scalar(colors[i%8]), 2); 
		}
	}

	// Обработка изображения библиотекой OpenCV завершена, конвертируем данные в формат Qt
	qmag = QImage((const uchar *)src.data, src.cols, src.rows, QImage::Format_RGB888).rgbSwapped();
	// Вызываем статический метод fromImage, для преобразования типа QImage, в тип QPixmap
	*qpix = QPixmap::fromImage(qmag);

	// Выводим обработанное изображение в окне программы
	ui.label->setPixmap(*qpix);
}
// Оптимизированный алгоритм
void Face_detection::face_search(cv::Mat &src, cv::Mat &temp , double width, double height)
{

	QImage qmag;

	// Формируем  разрешения кадра из переменных width_pix, height_pix
		cv::resize(src, src, Size(width,height), INTER_LINEAR);
	

	// Запускаем основной алгоритм поиска, если чек-бокс включен
	if (ui.checkBox->isChecked())
	{
 
	//Уменьшаем разрешение изображения на 50%
	// Изображение с уменьшенным разрешением сохраняем в матрицы - tmp
			cv::resize(src, temp, Size(), 0.5, 0.5);

	// Определения координат лица на изображении с помошью каскада Харра
	// Контейнер для хранения координат - вектор, из стандартной библиотеки STL
	// Раземер скользящего окна - 30x30 пикселя. 
		haar_cascade->detectMultiScale(
			temp, // Источник
			vector_objekt,  // Приемник, будет сохранено не изображение а координаты искомого объекта
			1.3, // Коофициент увеличения масшатаба
			3, // Минимальное число соседних областенй, значение которых будет учитывать в принятии решения: это лицо или нет?
			CV_HAAR_DO_CANNY_PRUNING, // Константа, позволяет пропускать области на изображении, в которых лица не может быть ни при каких обстоятельствах.
			Size(30,30) // Размер "скользяшего окна", при перемешении которго осушествляется анализ изображения.
			);

	// контейнер с координатами обрабатывается в цикле.
	// На исходном изображении рисуется прямоугольник, процедура rectangle() из библиотеки OpenCV. Цвет сторон парямоугольника, задается
	// вызовом процедуры - Scalar(), аргументы процедуры - цвет, толшина линии.
	// Цвет сторон прямоугольника задается из списка - colors, который был определен в конструкторе.
		for (int i = 0; i < vector_objekt.size(); i++)
			{
	// Работаем над координатами.
	// Так как изображение которое подвергалось анализу имеет размер = 1/2 от оригинального изображения, то
	// координаты интересуюших областей уменьшены в 2 раза, следовательно полученные координаты областей
	// на "маленьком" изображении нужно увеличить в два раза.
				vector_objekt[i].x = vector_objekt[i].x * 2;
				vector_objekt[i].y = vector_objekt[i].y * 2;
	// увеличиваем ширину и высоту квадрата в 2 раза.
				vector_objekt[i].width = vector_objekt[i].width * 2;
				vector_objekt[i].height = vector_objekt[i].height * 2;
	// Рисуем квадрат на тех частях изображения, где было обнаружено лицо. Цвет ребер берем из списка сolors. 
	// Номер элемента, в списке определям как отстаток от делеения i/8, толшина сторон квадрата равна 2.
				rectangle(src, vector_objekt[i], Scalar(colors[i%8]), 2); 
			}
	}
	

	// Обработка изображения библиотекой OpenCV завершена, конвертируем данные в формат Qt
		qmag = QImage((const uchar *)src.data, src.cols, src.rows, QImage::Format_RGB888).rgbSwapped();
	// Вызываем статический метод fromImage, для преобразования типа QImage, в тип QPixmap
		*qpix = QPixmap::fromImage(qmag);

	// Выводим обработанное изображение в окне программы
		ui.label->setPixmap(*qpix);
	
	
		
}

void Face_detection::on_actionCapture_opencv()
{
	// Использование класса Mat из OpenCV в качестве контейнера для кадра
		Mat mat_img;

		// Создаем временную матрицу
		Mat tmp;
	
	// Если метод вернет лож, то за счет логического "НЕ" лож будет преобразована в истину, что привет к остановке таймера и выходу из цикла
	// воспроизведения
		if (!file->read(mat_img))
		{
			fps_time->stop();
			time->stop();
	// Сохраняем значение времени выполнения
			int time_run = time_zaderjka->elapsed();
	// Вычисляем частоту вывода видео после обработки			
			float fps_2 = fps_summ/(time_run/1000);
	// Сбрасываем сумму кадров и выводим результат в окне программы
			fps_summ = 0;
			ui.label_7->setText(QString::number(fps_2)+"k/s");
	// Определяем задержку вывода видеопотока
	// по формуле:  Latentnosty = (fps_original - fps_posle_obrabotki)*(fps_original/100)
			float fps_original = file->get(CV_CAP_PROP_FPS);
			float Latentnosty = (fps_original - fps_2)*(fps_original/100);
	// выводм результат в главное окно программы
			ui.label_9->setText(QString::number(Latentnosty) +"%");
		
		} else
		{
	// Если оптимизация не отключена
			if (!ui.checkBox_2->isChecked()) 
			face_search(mat_img, tmp, width_pix, height_pix);
			else
	// Если оптимизация отключена
			face_search(mat_img, width_pix, height_pix);
	
	// Увеличиваем значения счетчика кадров, для определения частоты
			fps_detect++;
			
		
		}

	// Освобождаем ресурсы
		tmp.release();
		mat_img.release();	
}
void Face_detection::on_actionCapture_opencv_camera()
{
	// Использование класса Mat из OpenCV в качестве контейнера для кадра
		Mat mat_img;
		Mat tmp;
	// Загружаем кадр в контейнер
		*file >> mat_img;

	face_search(mat_img, tmp); // Вызываем метод детектирования лица
	// Счетчик кадров
		fps_detect++;
	// Освобождаем ресурсы
		mat_img.release();
		tmp.release();
}
void Face_detection::fps_count()
{	
	
	// Суммирование кадров
		fps_summ += fps_detect;
		ui.FPS_2->setText(QString::number(fps_detect)+"k/s");
	// Обнуляем счетчик кадров
		fps_detect = 0;
}

void Face_detection::knopka_obzor()
{
		QString Name = QFileDialog::getOpenFileName(this, tr("Open File"), "");

		if (Name.isEmpty()) {
			QMessageBox::critical(this, tr("Error"), tr("Fail not found!"));
			return;
		}
	// Метод toLocal8Bit(), класса QString, возвращает локализованнуй строку в формате QByteArray - массив байт, тип которого не определен. 
	// Так как класс std::string  принимает на вход поток байт неопределенного типа, то преобразование байт в кодировку символов std::string
	// производятся автоматически средствами класса std::string. Данный подход гарантирует переносимость кода на разные платформы, за счет того
	// что не меняется глобальная кодировка символов установленная в операционной системе.
		fileName = Name.toLocal8Bit();

	// Устанавливаем значение переменной Name в поле ввода текста: LineEdit
		ui.lineEdit->setText(Name);

}

void Face_detection::radio_button_camera()
{
	
		stop_video(); // Остановить видео-поток принятый на обработку ранее
		en_ds_knopci(false);

	// Открываем поток с камеры
		file = new VideoCapture(0); // Устройство ввода видеопотока по умолчани. Первой устройство обнаруженое в системе
	
	// Проверка, удалось ли открыть поток
		if (!proverka_otkrxtiy())
				return;

	// Устанавливаем таймер - задержка вывода
		time = new QTimer(this);
	// Устанавливаем таймер для вычисления частоты кадров
		fps_time = new QTimer(this); // Создан таймер с интервалам срабатывания 1секунда

	connect(fps_time, SIGNAL(timeout()), this, SLOT(fps_count()));  // Соединения таймера со слотом, каждые 1000мс = 1с в процессе работы программы
		fps_time->start(1000); // Период запуска метода fps_count определен в 1секунду
		
	// Период запуска метода on_actionCapture_opencv() определяется значением утстановленного таймера time->start()
		connect (time, SIGNAL(timeout()), this, SLOT(on_actionCapture_opencv_camera()));
	// Устанавливаем временную задержку вызова метода on_actionCapture_opencv()
	// Временная задарежка определяется как отношение 1000 = 1секунда к значению частоты вывода
		time->start(1000/file->get(CV_CAP_PROP_FPS));
		
		

}

void Face_detection::radio_button_fail()
{
	// Остановить видео поток принятый на обработку ранее
		stop_video(); 
		en_ds_knopci(true);
}

bool Face_detection::proverka_otkrxtiy()
{
		if (!file->isOpened())
		{
	// Создаем сообщение
			QMessageBox mesBox;
			mesBox.setText("video fail or kamera not available!");
			mesBox.exec();
			file->~VideoCapture();
			en_ds_knopci(true);
			return false;
		}
	
		return true;

}

Face_detection::~Face_detection()
{
	// Явным образом вызываем диструкторы объектов для работы которых была выделена память в куче.
	// Но диструкторы вызываются только в том случаи если указатель на объект не равен нулю.
	
		haar_cascade->~CascadeClassifier();
		
		if (file)		
			file->~VideoCapture();
		if (qpix)
			qpix->~QPixmap();
		if (time)
			time->~QTimer();
		if (fps_time)
			fps_time->~QTimer();
		if (time_zaderjka)
			delete time_zaderjka;
		
	
}

