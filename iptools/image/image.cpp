#include "image.h"

image::image()
{
	data.numRows = data.numColumns = 0; 
	data.redChannel.clear();
	data.greenChannel.clear();
	data.blueChannel.clear();
}
/*-----------------------------------------------------------------------**/
image::image(image &img)
{
	this->copyImage(img);
}

/*-----------------------------------------------------------------------**/
image::image(int rows, int columns) 
{
	this->data.numRows = rows;
	this->data.numColumns = columns; 
	this->resize (rows, columns);
}

/*-----------------------------------------------------------------------**/
image::~image() 
{
	this->deleteImage();
}

/*-----------------------------------------------------------------------**/
bool image::isInbounds (int row, int col) 
{
	if ((row < 0) || (col < 0) || (col >= data.numColumns) || (row >= data.numRows))
		return false;
	else 
		return true;
}

/*-----------------------------------------------------------------------**/
void image::deleteImage() 
{
	this->data.numRows = this->data.numColumns = 0; 
	this->data.redChannel.clear();
	this->data.greenChannel.clear();
	this->data.blueChannel.clear();
}

/*-----------------------------------------------------------------------**/
void image::copyImage(image &img) 
{
	this->resize(img.getNumberOfRows() ,img.getNumberOfColumns());

	for (int i = 0; i<3; i++) 
	{
		this->setChannel(i, *img.getChannel(i));
	}
}

void image::resize (image example){
	resize(example.getNumberOfRows(),example.getNumberOfColumns());
}

/*-----------------------------------------------------------------------**/
void image::resize (int rows, int columns)
{
	int length = rows*columns;
	data.numRows = rows;
	data.numColumns = columns;
	data.redChannel.clear();
	data.greenChannel.clear();
	data.blueChannel.clear();

	data.redChannel.resize(length); 
	data.greenChannel.resize(length);
	data.blueChannel.resize(length);

}

/*-----------------------------------------------------------------------**/
void image::setNumberOfRows (int rows)
{
	data.numRows = rows;
}

/*-----------------------------------------------------------------------**/
void image::setNumberOfColumns (int columns)
{
	data.numColumns = columns;
}

/*-------------------------------------------------------------------*/
void image::setPixel(const int row, const int col, const int value) {
	//if outside of range, print error
	if( (row > data.numRows) || (col > data.numColumns) )
		cout<<"ERR: cannot write pixel "<<row<<','<<col<<"; pixel is outside of image.\n";
	data.redChannel [row*data.numColumns+col] = value; 
}


/*-------------------------------------------------------------------*/
void image::setPixel(const int row, const int col, const int rgb, const int value){
	//if outside of range, print error
	if( (row > data.numRows) || (col > data.numColumns) )
		cout<<"ERR: cannot write pixel "<<row<<','<<col<<"; pixel is outside of image.\n";

	switch (rgb) 
	{
		case RED: data.redChannel [row*data.numColumns+col] = value; break;
		case GREEN: data.greenChannel [row*data.numColumns+col] = value; break;
		case BLUE: data.blueChannel [row*data.numColumns+col] = value; break;
	}
}

/*-------------------------------------------------------------------*/
int image::getPixel(const int row, const int col){ 
	int r = row;
	int c = col;

	//if row or column outside of image, return use edge value
	if(row > data.numRows) r = data.numRows;
	if(col > data.numColumns) c = data.numColumns;
	return data.redChannel [r*data.numColumns+c]; 
}

/*-------------------------------------------------------------------*/
int image::getPixel(const int row, const int col, const int rgb) {
	int value;

	int r = row;
	int c = col;
	//if row or column outside of image, return use edge value
	if(row > data.numRows) r = data.numRows;
	if(col > data.numColumns) c = data.numColumns;
	switch (rgb)
	{
		case RED: value = data.redChannel [r*data.numColumns+c]; break;
		case GREEN: value = data.greenChannel [r*data.numColumns+c]; break;
		case BLUE: value = data.blueChannel [r*data.numColumns+c]; break;
	}
	return value;
}

/*-----------------------------------------------------------------------**/
int image::getNumberOfRows () 
{
	return data.numRows;
}

/*-----------------------------------------------------------------------**/
int image::getNumberOfColumns () 
{
	return data.numColumns;
}


/*-----------------------------------------------------------------------**/
vector<int>* image::getChannel (int rgb) 
{
	switch (rgb) {
		case RED:
		return &data.redChannel;
		break;
		case GREEN:
		return &data.greenChannel;
		break;
		case BLUE:
		return &data.blueChannel;
		break;
	}
}
	/*-----------------------------------------------------------------------**/
bool image::setChannel (int rgb, vector<int> &channel)
{
	if (channel.size() == this->getChannel(rgb)->size())
	{
		*(this->getChannel(rgb)) = channel;
		return true;
	}
	return false;
}


/*-------------------------------------------------------------------*/
bool image::save (const char* file)
{
	FILE *outfile;
	int flag;

	//fprintf(stderr, "\n Saving edge image in %s...\n", file);
	if ((outfile = fopen(file, "w")) == NULL) 
	{
		printf("Cannot open file, %s for writing.\n", file) ;
		return false;
	}

	if (strstr(file, ".ppm") != NULL) 
	{	/* PPM Color File*/
		flag = 0;
	}

	else flag = 1;

	if (flag)
		fprintf(outfile, "P5\n%d %d\n255\n", data.numColumns, data.numRows);
	else 
		fprintf(outfile, "P6\n%d %d\n255\n", data.numColumns, data.numRows);

	if (flag) 
	{
		for (int i=0; i < data.numRows; i++) 
		{
			for (int j=0; j < data.numColumns; j++)
			{
				int v = (data.redChannel [i*data.numColumns+j]>255)?255:data.redChannel [i*data.numColumns+j];
				putc((unsigned char) (
					((data.redChannel [i*data.numColumns+j])>255)?255:(data.redChannel [i*data.numColumns+j]) ), outfile) ;
			}
		}
	}
	else {
		for (int i=0; i < data.numRows; i++) 
		{
			for (int j=0; j < data.numColumns; j++) 
			{
				putc((unsigned char) (((data.redChannel [i*data.numColumns+j])>255)?255:(data.redChannel [i*data.numColumns+j])), outfile) ;
				putc((unsigned char) (((data.greenChannel [i*data.numColumns+j])>255)?255:(data.greenChannel [i*data.numColumns+j])), outfile) ;
				putc((unsigned char) (((data.blueChannel [i*data.numColumns+j])>255)?255:(data.blueChannel [i*data.numColumns+j])), outfile) ;
			}
		}
	}

	fclose(outfile);
	return true;
}

/*-------------------------------------------------------------------*/
bool image::save (char* file)
{
	const char* name = file;
	save(name);
}
	/*-------------------------------------------------------------------*/

/*bool read ( char* file){
	const char* name = file;
	return read(name);
}
bool image::read (const char * file) {*/
bool image::read (char *file){
	FILE *fp;
	char str[50];
	unsigned char r, g, b;
	int i, flag;

	if (strstr(file, ".ppm") != NULL) {/* PPM Color File*/
		flag = 0;
	} else flag = 1;

	if ((fp = fopen(file, "r")) == NULL) {
		fprintf(stderr, "\nCannot open image file %s\n", file);
		exit(1);
	}

	fscanf(fp, "%s", str) ;
	if ((flag == 0) && (strcmp (str, "P6") != 0)) {
		fprintf(stderr, "\n image file %s not in PPM format...%s", file, str);
		return false;
	}
	if ((flag == 1) && (strcmp (str, "P5") != 0)) {
		fprintf(stderr, "\n image file %s not in PGM format...%s", file, str);
		return false;
	}

	data.numColumns = getint(fp);
	while (data.numColumns == -1 || data.numColumns == 0)
		data.numColumns = getint(fp);

	while (data.numRows == -1 || data.numRows == 0)
		data.numRows = getint(fp);
	resize (data.numRows,data.numColumns);
	fscanf(fp, "%d", &i) ;  
	(getc(fp));/* gets the carriage return*/
	if (flag){
		for (i=0; i < data.numRows*data.numColumns; i++) 
		{
			r = (unsigned char) (getc(fp));  
			data.redChannel [i] = r;
		}
	} else {
		for (i=0; i < data.numRows*data.numColumns; i++) 
		{
			r = (unsigned char) (getc(fp));  
			g = (unsigned char) (getc(fp));  
			b = (unsigned char) (getc(fp));
			data.redChannel [i] = r;
			data.greenChannel [i] = g;
			data.blueChannel [i] = b;
		}
	} 

	fclose(fp);
	return true;
}

/*-----------------------------------------------------------------------**/
int image::getint(FILE *fp) 
{
	int item, i, flag;

/* skip forward to start of next number */
	item  = getc(fp); flag = 1;
	do {

		if (item =='#') {   /* comment*/
			while (item != '\n' && item != EOF) item=getc(fp);
		}

		if (item ==EOF) { return 11;}	//TODO: I have no idea what this function does, but returning 0 here as it was creates an infinite loop
		if (item >='0' && item <='9') 
			{flag = 0;  break;}

	/* illegal values */
		if ( item !='\t' && item !='\r' && item !='\n' && item !=','){
			cout<<"ERR: illegal value for item\n";
			return(-1);
		}
		item = getc(fp);
	} while (flag == 1);

/* get the number*/
	i = 0; flag = 1;
	do {
		i = (i*10) + (item - '0');
		item = getc(fp);
		if (item <'0' || item >'9') {
			flag = 0; break;}
			if (item==EOF) break; 
	} while (flag == 1);
	return i;
}




