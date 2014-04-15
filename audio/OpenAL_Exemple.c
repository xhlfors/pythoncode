//
//  OpenAL_Exemple.c
//  pythoncode
//
//  Created by ys-zhang on 4/15/14.
//  Copyright (c) 2014 ys-zhang. All rights reserved.
//

/***************************************************************************
 openal全教程
 分类： OpenSceneGraph 2008-12-01 16:22 3015人阅读 评论(1) 收藏 举报
 openal教程（一）
 简介L一直在不断
 欢迎来到OPENAL的世界！OPENA的创新，几乎没有一个API能达到
 她的全部潜能。一个很大的原因是因为hardware加速建立在特殊的版卡上。然而，
 Creative Labs是APENAL的主要支持者，同时也是最大声卡厂商之一。OPENAL的另
 一个主要支持者LOKI。
 OPENAL不是商业产品，那样做限制了她的发展。我只知道再PC游戏中用OPENAL。
 OPENAL有许多的潜能，有许多的声音库工作在最地层的hardware上。但OPENAL的
 设计者经过无数的测试使她成为一个高级的API。她的风格是自由的，不同的编码
 风格和hardware部件将充分运用她的功能。有OPENGL编程精练的人将很快掌握OPEN
 AL。OPENAL有建立3D环境音效的能力。
 OPENAL是very cool,她是一个非常清晰的API并且能熔入你的代码。你将做出
 很COOL的音效，下面让我们进入COOL COOL的OPENAL世界。
 *******************************************************************************/

#include <conio.h>
#include <stdlib.h>
#include <al/al.h>
#include <al/alc.h>
#include <al/alu.h>
#include <al/alut.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

/*
 你会发现再OPENAL头和OPENGL头的定义上有许多的相似之处。除了“al.h","al
 u.h","alut.h"与”gl.h","glu.h","glut.h"相似，还增加了一个"alc.h".ALC（
 AUDIO LIBRARY CONTEXT）处理声音通过不同的平台，她也处理你在几个窗口下共
 享设备的环境。
 */

// 存储声音数据
ALuint Buffer;

// 用于播放声音
ALuint Source;

/*
 这是程序处理结构的初始化。在OPENAL中三种不同的结构，所有关于声音播放和
 声音数据存储在一个内存中，源（source）是指向放声音的空间。明白源是非常
 的重要。源只播放内存中的背景声音数据。源也给出了特殊的属性如位置和速度。
 第三个对象是听者，用户就是那唯一的听者。听者属性属于源属性，决定如何
 听声音。例如，不同位置将决定声音的速度。
 */

// 源声音的位置
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// 源声音的速度
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };


// 听者的位置
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// 听者的速度
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// 听者的方向 (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

/*
 在上面的代码中，我们定义了源和听者对象的位置和速度。这些数组是基于笛
 卡儿坐标的矢量。你能很容易用结构或类做相同的事情。
 */

ALboolean LoadALData()
{
    // 载入变量.
    
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;
    //在这里我们建立一个函数用于从一个文件中载入声音数据。变量用于存储适合
	//我们的ALUT信息。
	
    // 载入WAV数据
    alGenBuffers(1, &Buffer);
    if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
    alutLoadWAVFile("wavdata/FancyPants.wav", &format, &data, &size, &freq, &loop);
    alBufferData(Buffer, format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);
    /*
     函数alGenBufers用于建立对象内存并把他们存储在我们定义的变量中。然后判断
     数据是否存储。
     ALUT库为我们打开文件，提供我们建立内存所需的信息，并且在我们归属所有
     数据到内存后，她将处理这些数据。
     */
    // 捆绑源
    alGenSources(1, &Source);
    
    if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
    alSourcei (Source, AL_BUFFER,   Buffer   );
    alSourcef (Source, AL_PITCH,    1.0f     );
    alSourcef (Source, AL_GAIN,     1.0f     );
    alSourcefv(Source, AL_POSITION, SourcePos);
    alSourcefv(Source, AL_VELOCITY, SourceVel);
    alSourcei (Source, AL_LOOPING,  loop     );
    /*
     我们用建立内存对象的方法建立了源对象。然后，我们定义源属性用于录放。
     最重要的属性是她用的内存。这告诉源用于录放。因此，我们只有捆绑她。同时，
     我们也告诉她我们定义的源位置和速度。
     */
    // 做错误检测并返回
    if (alGetError() == AL_NO_ERROR)
    return AL_TRUE;
    
    return AL_FALSE;
    //在函数的结尾，我们将做更多的检测，以确定她的正确。
}
void SetListenervalues()
{
    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}
//我们建立一个函数用于更新听者速度。
void KillALData()
{
    alDeleteBuffers(1, &Buffer);
    alDeleteSources(1, &Source);
    alutExit();
}
//这是一个关闭函数，用于释放内存和音频设备。
int main(int argc, char *argv[])
{
    // 初始OPENAL并清错误字节
    
    alutInit(&argc, argv);
    alGetError();
    /*
     函数alutInit将安装ALC需要的东西。ALUT通过ALC并设置她为当前建立OPENAL
     环境描述。在WINDOWS平台上初始DIRECTSOUND。然后用‘GLGETERROR’检测错误。
     */
    // 载入WAV数据
    if (LoadALData() == AL_FALSE)
    return -1;
    
    SetListenervalues();
    
    // 设置退出函数
    atexit(KillALData);
	
    //我们将检测WAV文件是否正确载入。如果没有退出程序。正确后，更新听者参数，最后退出。
    ALubyte c = ' ';
    
    while (c != 'q')
    {
        c = getche();
        
        switch (c)
        {
                // Pressing 'p' will begin playing the sample.
            case 'p': alSourcePlay(Source); break;
                
                // Pressing 's' will stop the sample from playing.
            case 's': alSourceStop(Source); break;
                
                // Pressing 'h' will pause (hold) the sample.
            case 'h': alSourcePause(Source); break;
        };
    }
    
    return 0;
}

/*********************************************************************************
 This is the interesting part of the tutorial. It's a very basic loop that lets us
 control the playback of the audio sample. Pressing 'p' will replay the sample,
 pressing 's' will stop the sample, and pressing 'h' will pause the sample.
 Pressing 'q' will exit the program.
 
 Well there it is. Your first delve into OpenAL. I hope it was made simple enough
 for you. It may have been a little too simple for the 1337 h4X0r, but we all got to
 start somewhere. Things will get more advanced as we go along.
 
 Download the Dev-C++ source and project file
 
 
 OpenAl教程（二）
 
 循环和消退
 
 希望你觉得上一章有用，这一章将更容易。
 
 ************************************************************************************/
#include
#include
#include
#include
#include
#include
#include

// 存储声音数据.
ALuint Buffer;

// 用于播放声音.
ALuint Source;

// 源声音的位置.
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// 源声音的速度.
ALfloat SourceVel[] = { 0.0, 0.0, 0.1 };

// 听者的位置.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// 听者的速度
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// 听者的方向 (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
//这一章与上一章唯一的不同是源速度的改变，他的‘Z’现在是0.1.

ALboolean LoadALData()
{
	// 载入变量
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;
    
	// 载入WAV数据.
    
	alGenBuffers(1, &Buffer);
    
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	alutLoadWAVFile("wavdata/Footsteps.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	// 捆绑源
    
	alGenSources(1, &Source);
    
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	alSourcei (Source, AL_BUFFER, Buffer );
	alSourcef (Source, AL_PITCH, 1.0f );
	alSourcef (Source, AL_GAIN, 1.0f );
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei (Source, AL_LOOPING, AL_TRUE );
    
	// 做错误检测并返回
    
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	return AL_TRUE;
}

//在这一节中有两处改变，首先是导入“FOOTSTES。WAV”，设置源‘AL_LOOPING’
//为‘AL_TRUE’。这意味着源播放直到停止时结束。他将不断的循环播放。
void SetListenervalues()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}
//这里没有改变。
int main(int argc, char *argv[])
{
	// 初始OPENAL并清错误字节
	alutInit(NULL,0);
	alGetError();
    
	// 载入WAV数据.
	if (LoadALData() == AL_FALSE)
    return 0;
    
	SetListenervalues();
    
	// 设置退出函数.
	atexit(KillALData);
    
	// 开始源的播放.
	alSourcePlay(Source);
    
	//循环
	ALint time = 0;
	ALint elapse = 0;
    
	while (!kbhit())
	{
		elapse += clock() - time;
		time += elapse;
        
		if (elapse > 50)
		{
			elapse = 0;
            
			SourcePos[0] += SourceVel[0];
			SourcePos[1] += SourceVel[1];
			SourcePos[2] += SourceVel[2];
            
			alSourcefv(Source, AL_POSITION, SourcePos);
		}
	}
    
    
	return 0;
}

//这里唯一的改变是增加了一个循环。他将代替播放和停止按钮。
We do this by slowly incrementing the position by it's velocity over
time. The time is sampled by checking the system clock which gives
us a tick count. It shouldn't be necessary to change this, but if the
audio clip fades too fast you might want to change 50 to some higher n
umber. Pressing any key will end the loop

/**************************************************************************
 多源
 
 你好，在这一章中，我们将在上一章的例程中加入一些元素，使他能同时播放超过一种的音乐。
 通常在一个优秀的游戏中有各种不同的音夹（clip),这是怎样实现的呢？
 下面将介绍。
 *****************************************************************************/
#include
#include
#include
#include
#include
#include
#include

// 我们需要的最大的数据缓冲.
#define NUM_BUFFERS 3

// 我们需要放三种声音.
#define NUM_SOURCES 3

// 缓冲和源标志.
#define BATTLE 0
#define GUN1 1
#define GUN2 2

// 存储声音数据.
ALuint Buffers[NUM_BUFFERS];

// 用于播放声音.
ALuint Sources[NUM_SOURCES];

// 源声音的位置.
ALfloat SourcesPos[NUM_SOURCES][3];

// 源声音的速度.
ALfloat SourcesVel[NUM_SOURCES][3];


// 听者的位置.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// 听者的速度.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// 听者的方向 (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

//在这一章中，唯一的不同是多了3种将导入Openal系统的不同的声音效果 。

ALboolean LoadALData()
{
	// 载入变量.
    
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;
    
	// 载入WAV数据.
    
	alGenBuffers(NUM_BUFFERS, Buffers);
    
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	alutLoadWAVFile("wavdata/Battle.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[BATTLE], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/Gun1.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[GUN1], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/Gun2.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[GUN2], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	// 捆绑源.
    
	alGenSources(NUM_SOURCES, Sources);
    
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	alSourcei (Sources[BATTLE], AL_BUFFER, Buffers[BATTLE] );
	alSourcef (Sources[BATTLE], AL_PITCH, 1.0 );
	alSourcef (Sources[BATTLE], AL_GAIN, 1.0 );
	alSourcefv(Sources[BATTLE], AL_POSITION, SourcePos[BATTLE]);
	alSourcefv(Sources[BATTLE], AL_VELOCITY, SourceVel[BATTLE]);
	alSourcei (Sources[BATTLE], AL_LOOPING, AL_TRUE );
    
	alSourcei (Sources[GUN1], AL_BUFFER, Buffers[GUN1] );
	alSourcef (Sources[GUN1], AL_PITCH, 1.0 );
	alSourcef (Sources[GUN1], AL_GAIN, 1.0 );
	alSourcefv(Sources[GUN1], AL_POSITION, SourcePos[GUN1]);
	alSourcefv(Sources[GUN1], AL_VELOCITY, SourceVel[GUN1]);
	alSourcei (Sources[GUN1], AL_LOOPING, AL_FALSE );
    
	alSourcei (Sources[GUN2], AL_BUFFER, Buffers[GUN2] );
	alSourcef (Sources[GUN2], AL_PITCH, 1.0 );
	alSourcef (Sources[GUN2], AL_GAIN, 1.0 );
	alSourcefv(Sources[GUN2], AL_POSITION, SourcePos[GUN2]);
	alSourcefv(Sources[GUN2], AL_VELOCITY, SourceVel[GUN2]);
	alSourcei (Sources[GUN2], AL_LOOPING, AL_FALSE );
    
	// 做错误检测并返回
    
	if( alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	return AL_TRUE;
}
//首先，我们导入文件数据到3个缓冲区，然后把3个缓冲区和3个源锁在
//一起。唯一的不同是文件“battle.wav”在不停止时循环。
void SetListenervalues()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void KillALData()
{
	alDeleteBuffers(NUM_BUFFERS, &Buffers[0]);
	alDeleteSources(NUM_SOURCES, &Sources[0]);
	alutExit();
}
//在这段代码中，我们没有改变。
int main(int argc, char *argv[])
{
	// Initialize OpenAL and clear the error bit.
	alutInit(NULL, 0);
	alGetError();
    
	// Load the wav data.
	if (LoadALData() == AL_FALSE)
    return 0;
    
	SetListenervalues();
    
	// Setup an exit procedure.
	atexit(KillALData);
    
	// Begin the battle sample to play.
	alSourcePlay(Sources[BATTLE]);
    
	// Go through all the sources and check that they are playing.
	// Skip the first source because it is looping anyway (will always be playing).
	ALint play;
    
	while (!kbhit())
	{
		for (int i = 1; i < NUM_SOURCES; i++)
		{
			alGetSourcei(Sources[i], AL_SOURCE_STATE, &play);
            
			if (play != AL_PLAYING)
			{
				// Pick a random position around the listener to play the source.
                
				double theta = (double) (rand() % 360) * 3.14 / 180.0;
                
				SourcePos[i][0] = -float(cos(theta));
				SourcePos[i][1] = -float(rand()%2);
				SourcePos[i][2] = -float(sin(theta));
                
				alSourcefv(Sources[i], AL_POSITION, SourcePos[i] );
                
				alSourcePlay(Sourcev[i]);
			}
		}
	}
    
	return 0;
}

/*****************************************************************************
 这段是这篇文章最有趣的地方。我们在这里将播放。如果他不播放，我们将在3D空间中选
 一个点播放（点击）。
 
 And bang! We are done. As most of you have probably seen, you don't have to do
 anything special to play more than one source at a time. OpenAL will handle all
 the mixing features to get the sounds right for their respective distances and
 velocities. And when it comes right down to it, isn't that the beauty of OpenAL?
 
 You know that was a lot easier than I thought. I don't know why I waited so long
 to write it. Anyway, if anyone reading wants to see something specific in future
 tutorials (not necessarily pertaining to OpenAL, I have quite an extensive
 knowledge base) drop me a line at lightonthewater@hotmail.com I plan to do tutorials
 on sharing buffers and the Doppler effect in some later tutorial unless there is
 request for something else. Have fun with the code!
 
 ALC
 
 Alut一直为我们做着所有神奇的东西。例如处理音频设备。ALUT库为我们提供这些功能，但是
 一些机灵的程序员想知道他是怎样工作的。
 
 我们可以这样想，在一些点上直接用ALC。
 
 在这一章中，我们将讲述ALC层，并看一下他是怎样处理设备的。
 **********************************************************************************/
ALCdevice* pDevice;

ALCubyte DeviceName[] = "DirectSound3D";

pDevice = alcOpenDevice(DeviceName);

/*
 当然，ALC设备是什么？可以这样想，在共享整个系统下，OPENAL夺取了设备的句柄。在我们用
 DIRECTSOUND作为音频设备时，设备能完成的很好。
 
 程序从设备中夺取句柄并为程序准备着。
 
 传递NULL给‘alcOpenDevice',他将使ALC用默认设备。
 */

ALCcontext* pContext;

pContext = alcCreateContext(pDevice, NULL);

alcMakeContextCurrent(pContext);

/*
 ALC文本描述是什么？
 
 OPENGL程序员能撤消通过不同窗口的状态管理的控制的精简文本描述。HGLRC能被挑调用建立多次，
 使多描述窗口成为可能。并且不同的文本描述状态可以实现。ALC文本描述工作在相同的原理下。
 首先，我们告诉他我们用的设备，然后我们做当前的文本描述。理论上你能为不同的窗口建立多
 个表达文本描述，并且设置不同的状态变量，以使他们能很好的工作。尽管“表达文本描述”用于
 可视表达。
 
 你可能也注意到“alcCreateContext'中的第二个变量是NULL。
 
 OPENAL中
 下面的变量与他有关。
 ALC_FREQUENCY
 ALC_REFRESH
 ALC_SYNC
 
 你可以调用’alcMakeContextCurrent'替换你建立的多个文本描述。同样
 在'alcMakeContextCurrent'中置NULL。他将防止处理其他声音数据。要意
 识到当你有多个表达文本描述时，你只能在当前用一个。并且当你的程序要
 交换使用两个描述时，必须确定当前使用的描述是在当前。当你想不通过大的
 检查，知道用的哪个描述，必须用这些。
 */

ALcontext* pCurContext;
pCurContext = alcGetCurrentContext();
//通过文本描述，你能获取设备。
ALdevice* pCurDevice;
pCurDevice = alcGetContextsDevice(pCurContext);

//在我们用文本描述时，我们必须收回用的设备。在处理文本描述时，有更COOL的方法。

alcSuspendContext(pContext);
// 终止pContext.
alcProcessContext(pContext);
// 重置pContext.

//当程序停止时，我们必须重置声音数据到文本描述。当程序暂停时，文本描述中的数据不
//会产生声音。在程序运行期间，源或缓冲区的‘lifetime'的有效是由源或缓冲器ID的合法性决定的。

alcMakeContextCurrent(NULL);
alcDestroyContext(pContext);
alcCloseDevice(pDevice);

//最后，怎样清出他呢？当前文本描述被初始化为’NULL‘，描述释放并且设备句柄交还系统。
//在这里我们只讲了一些ALC的基本功能。

ALenum alcGetError(ALvoid);

ALboolean alcIsExtensionPresent(ALCdevice* device, ALubyte* extName);

ALvoid* alcGetProcAddress(ALCdevice* device, ALubyte* funcName);

ALenum alcGetEnumvalue(ALCdevice* device, ALubyte* enumName);

ALubyte* alcGetString(ALCdevice* device, ALenum token);

ALvoid alcGetIntegerv(ALCdevice* device, ALenum token, ALsizei size, ALint* dest);

/*
 这些做什么，我们肯定很清楚，首先，我们用'alcGetError' 检测错误。
 
 下面三个功能是询问ALC的扩展。这在开始就应计划。最后alcGetInteger'将返回ALC的版本
 'ALC_MAJOR_VERSION'or 'ALC_MINOR_VERSION'。
 
 函数'alcGetString'返回下面信息：
 ALC_DEFAULT_DEVICE_SPECIFIER
 ALC_DEVICE_SPECIFIER
 ALC_EXTENSIONS
 
 首先是OPENAL完成的设备的信息。OPENAL 返回"DirectSound3D",
 第二个返回"DirectSound" ；
 
 最后一个返回NULL。
 
 Well that's most of Alc for you. I hope it gave you a better understanding of how
 OpenAL interacts with the operation system. You might try writing your own
 initialization routines so you can cast off Alut altogether. Either way have fun with it.
 
 See the Java Bindings for OpenAL page for the Java version of this tutorial - adapted
 by: Athomas Goldberg
 */

/*********************************************************************************
 源共享缓冲区
 
 在这一章中，我们将讲解如何在你的缓冲区中共享多个源。这是个非常合理，自然的步骤，非常的容易。
 你完全可以跳过这章。但对于愿意读这一章的朋友，你将发现他非常有趣。我们将准备好ALC层以便我
 们能用第四章的知识。
 
 让我们开始吧，在这一章中，我们将用的矢量来自标准模板库，因此，确定你是否安装了他，最好还有
 一些关于他的知识。在这一章中，我不会讲STL。
 **********************************************************************************/

// 表明缓冲区.
#define THUNDER 0
#define WATERDROP 1
#define STREAM 2
#define RAIN 3
#define CHIMES 4
#define OCEAN 5

#define NUM_BUFFERS 6


// 存贮声音数据.
ALuint Buffers[NUM_BUFFERS];

// 播放多个声音的源的矢量表
vector<ALuint> Sources;
//首先，我写出了我们用于表明缓冲区数组的一些指令。我们将用几个WAV文件，因此我们
//需要几个缓冲区。我们将用一个STL矢量代替用于存贮源的一个数组。我们能做这些是因为
//他让我们能有一个源的动态数。我们能一直添加源到场景，直到OPENAL脱离他们运行。

ALboolean InitOpenAL()
{
	ALCdevice* pDevice;
	ALCcontext* pContext;
	ALCubyte* deviceSpecifier;
	ALCubyte deviceName[] = "DirectSound3D";
    
	// 得到设备句柄
	pDevice = alcOpenDevice(deviceName);
    
	// 得到设备说明.
	deviceSpecifier = alcGetString(pDevice, ALC_DEVICE_SPECIFIER);
    
	printf("Using device '%s'./n", szDeviceSpecifier);
    
	// 建立声音文本描述.
	pContext = alcCreateContext(pDevice, NULL);
    
	// 设置行为文本描述.
	alcMakeContextCurrent(pContext);
    
	// 检查错误.
	if (alcGetError() != ALC_NO_ERROR)
    return AL_FALSE;
    
	return AL_TRUE;
}

//这是来自上一章的代码。首先，我们得到 "DirectSound3D"设备的句柄，然后获得用
//于程序的表明文本描述。这个文本描述设置当前，函数将检查在我们返回成功前，是否出错。

void ExitOpenAL()
{
	ALCcontext* pCurContext;
	ALCdevice* pCurDevice;
    
	// 得到当前文本描述
	pCurContext = alcGetCurrentContext();
    
	// 得到用于当前文本描述的设备?
	pCurDevice = alcGetContextsDevice(pCurContext);
    
	// 重置当前文本描述为NULL
	alcMakeContextCurrent(NULL);
    
	//释放文本描述和设备
	alcDestroyContext(pCurContext);
	alcCloseDevice(pCurDevice);
}

//我们用和释放的文本描述和设备将收回。另外，在OPENAL暂停程序时，设置当前
//文本描述为NULL。但是这些都不可预料。如果你用了多个文本描述，你也许需要更
//好的方法来做这些事。我将介绍一些比较好的方法。

ALboolean LoadALData()
{
	// 导入的变量
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;
    
	// 装载WAV文件到缓冲区
	alGenBuffers(NUM_BUFFERS, Buffers);
    
	if(alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	alutLoadWAVFile("wavdata/thunder.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[THUNDER], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/waterdrop.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[WATERDROP], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/stream.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[STREAM], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/rain.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[RAIN], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/ocean.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[OCEAN], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	alutLoadWAVFile("wavdata/chimes.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[CHIMES], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
    
	// 错误检测
	if (alGetError() != AL_NO_ERROR)
    return AL_FALSE;
    
	return AL_TRUE;
}

//在这个函数中，我将移动产生源，这是因为我们将一个一个的初始化。
void AddSource(ALint type)
{
	ALuint source;
    
	alGenSources(1, &source);
    
	if (alGetError() != AL_NO_ERROR)
	{
		printf("Error generating audio source.");
		exit(-1);
	}
    
	alSourcei (source, AL_BUFFER, Buffers[type]);
	alSourcef (source, AL_PITCH, 1.0 );
	alSourcef (source, AL_GAIN, 1.0 );
	alSourcefv(source, AL_POSITION, SourcePos );
	alSourcefv(source, AL_VELOCITY, SourceVel );
	alSourcei (source, AL_LOOPING, AL_TRUE );
    
	alSourcePlay(source);
    
	Sources.push_back(source);
}

//这个函数将产生源，他将为我们载入的缓冲区中的一个产生一个源。用‘TYPE’表示缓冲区，
//我们文章开始建立的指令将做这些事情。然后做错误检测，确定源能播放。如果源不能将退出。

void KillALData()
{
	for (vector<ALuint>::iterator iter = Sources.begin(); iter != Sources.end(); ++iter)
    alDeleteSources(1, iter);
	Sources.clear();
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	ExitOpenAL();
}

//这个函数将修改STL表。我们不得不删除每个源并且清除表上的内容。

ALubyte c = ' ';

while (c != 'q')
{
	c = getche();
    
	switch (c)
	{
		case 'w': AddSource(WATERDROP); break;
		case 't': AddSource(THUNDER); break;
		case 's': AddSource(STREAM); break;
		case 'r': AddSource(RAIN); break;
		case 'o': AddSource(OCEAN); break;
		case 'c': AddSource(CHIMES); break;
	};
}

//这是程序的主函数，他等待键盘输入，建立源，播放声音。
/*
 The program can be expanded for using more wav files, and have the added feature of placing
 the sources around the scene in arbitrary positions. You could even allow for sources to
 play with a given frequency rather than have them loop. However this would require GUI routines
 that go beyond the scope of the tutorial. A full featured "Weathering Engine" would be a nifty
 program to make though. ;)
 */

/*****************************************************************************************
 高级导入和错误处理
 
 虽然现在，我们能做出一些漂亮的东西，但是这些都没有要求我们精确的处理他们。原因是
 我们写的代码是为了便于学习。因此，我们将移进一些高级的东西。最重要的是我们将学习
 更高级的处理错误的方法。我们也将重新改写载入声音数据的方法。我们首先考虑这些函数
 将做什么。
 ********************************************************************************/

string GetALErrorString(ALenum err);
/*
 * 1) 识别错误代码
 * 2)返回错误
 */


ALuint LoadALBuffer(string path);
/*
 * 1) 建立缓冲区
 * 2) 导入WAV文件
 * 3) 返回缓冲区ID
 */

ALuint GetLoadedALBuffer(string path);
/*
 * 1) 检测文件是否载入
 * 2) 如果载入，返回缓冲区ID
 * 3) 如果失败，重新载入并返回缓冲区ID
 */

ALuint LoadALSample(string path, bool loop);
/*
 * 1) 建立源
 * 2) 调用‘GtLoadedALBuffer' 中的’PATH‘加载文件?
 * 3)返回源ID
 */

void KillALLoadedData();
/*
 * 1)释放数据?
 */

bool LoadALData();
/*
 * 1) 载入所有的源和缓冲区
 */

void KillALData();
/*
 * 1) 释放所有的缓冲区
 * 2) 释放所有的源
 */

vector<string> LoadedFiles; // 文件路径
vector<ALuint> Buffers; // 缓冲区.
vector<ALuint> Sources; // 源.

//看一下这个函数，想一下他做什么。我们试着建立一个关于缓冲区和源的系统。
//我们能调用来自文件的源并且系统能处理缓冲区的建立，因此，我们不用复制
//缓冲区。系统将处理缓冲区并且将有效的处理资源。

string GetALErrorString(ALenum err)
{
	switch(err)
	{
        case AL_NO_ERROR:
            return string("AL_NO_ERROR");
            break;
            
        case AL_INVALID_NAME:
            return string("AL_INVALID_NAME");
            break;
            
        case AL_INVALID_ENUM:
            return string("AL_INVALID_ENUM");
            break;
            
        case AL_INVALID_value:
            return string("AL_INVALID_value");
            break;
            
        case AL_INVALID_OPERATION:
            return string("AL_INVALID_OPERATION");
            break;
            
        case AL_OUT_OF_MEMORY:
            return string("AL_OUT_OF_MEMORY");
            break;
	};
}
//函数的功能是转换错误代码为字符。OPENAL SDK说返回'AL_OUT_OF_MEMORY' 是错误的，
//我们应认真对待所有错误，使我们的代码用最新的版本处理数据。

string GetALCErrorString(ALenum err)
{
	switch(err)
	{
        case ALC_NO_ERROR:
            return string("AL_NO_ERROR");
            break;
            
        case ALC_INVALID_DEVICE:
            return string("ALC_INVALID_DEVICE");
            break;
            
        case ALC_INVALID_CONTEXT:
            return string("ALC_INVALID_CONTEXT");
            break;
            
        case ALC_INVALID_ENUM:
            return string("ALC_INVALID_ENUM");
            break;
            
        case ALC_INVALID_value:
            return string("ALC_INVALID_value");
            break;
            
        case ALC_OUT_OF_MEMORY:
            return string("ALC_OUT_OF_MEMORY");
            break;
	};
}

//这个函数的功能是说明ALC错误。OPENAL和ALC共享ID，但是他们在一些功能上不相等。
//函数 'alGetError'应注意：OPENAL SDK定义一次只能得到一个错误。当函数被调用时，
//他返回他得到的第一个错误，并且清错误为'AL_NO_ERROR'

ALuint LoadALBuffer(string path)
{
	// Variables to store data which defines the buffer.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;
    
	// 缓冲区ID和错误检测变量
	ALuint buffer;
	ALenum result;
    
	// 产生缓冲区，看他是否成功建立.
	alGenBuffers(1, &buffer);
    
	if ((result = alGetError()) != AL_NO_ERROR)
    throw GetALErrorString(result);
    
	// 读WAV数据，检测是否成功。
	alutLoadWAVFile(szFilePath, &format, &data, &size, &freq, &loop);
    
	if ((result = alGetError()) != AL_NO_ERROR)
    throw GetALErrorString(result);
    
	// 装载WAV数据，检测是否成功
	alBufferData(buffer, format, data, size, freq);
    
	if ((result = alGetError()) != AL_NO_ERROR)
    throw GetALErrorString(result);
    
	// 出去临时数据
	alutUnloadWAV(format, data, size, freq);
    
	if ((result = alGetError()) != AL_NO_ERROR)
    throw GetALErrorString(result);
    
	//返回缓冲区ID
	return buffer;
}

//在导入数据时，我们做了错误检测。没有任何错误将通过。当数据导入时，没有足够
//的内存，WAV文件可能不退出，或者OPENAL函数中的错误数据将产生错误。

ALuint GetLoadedALBuffer(string path)
{
	int count = 0; // 'count' 表明缓冲区列表
    
	ALuint buffer; // 用于导入缓冲区的缓冲区ID
    
    
	// 重复列表中的每个文件
	for(vector<string>::iterator iter = LoadedFiles.begin(); iter != LoadedFiles.end(); ++iter, count++)
	{
		// 如果文件已经导入，返回他的缓冲区ID.
		if(*iter == path)
        return Buffers[count];
	}
    
	// 如果文件是新的，我们将为他建立缓冲区.
	buffer = LoadALBuffer(path);
    
	// 添加缓冲区到列表，记录他已添加.
	Buffers.push_back(buffer);
    
	LoadedFiles.push_back(path);
    
	return buffer;
}

//人们的麻烦通常在这里，但他确实不是很复杂。我们通过包含文件路径的列表来检索。
//如果其中一个符合要求，我们直接返回他的ID到缓冲区。我们通过这个函数导入我们
//的文件，这样就避免了复制时的浪费。每个文件应该保证在自己的列表中。'Buffers'
//表类士于'LoadedFiles'表。

ALuint LoadALSample(string path, bool loop)
{
	ALuint source;
	ALuint buffer;
	ALenum result;
    
	// 得到文件缓冲区ID
	buffer = GetLoadedALBuffer(path);
    
	// 产生源.
	alGenSources(1 &source);
    
	if ((result = alGetError()) != AL_NO_ERROR)
    throw GetALErrorString(result);
    
	// 设置源属性.
	alSourcei (source, AL_BUFFER, buffer );
	alSourcef (source, AL_PITCH, 1.0 );
	alSourcef (source, AL_GAIN, 1.0 );
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei (source, AL_LOOPING, loop );
    
	// 保存源ID.
	Sources.push_back(source);
    
	// 返回源ID.
	return source;
}

//现在我们已经建立处理缓冲区的系统，我们需要得到源的伸展。在这里，我们得到了
//导入文件的缓冲区ID。这个缓冲区是一个新源，我们保存他并返回。

void KillALLoadedData()
{
	LoadedFiles.clear();
}
//'gLoadedFilesv'存储在导入缓冲区的WAV文件的路径下，我们要处理他。
// 源ID's.

ALuint phaser1;
ALuint phaser2;

void LoadALData()
{
	// 你的应用在这里，不用担心缓冲区。 
	phaser1 = LoadALSample("wavdata/phaser.wav", false);
	phaser2 = LoadALSample("wavdata/phaser.wav", true);
    
	KillLoadedALData();
}

//他表示用于程序的所有的WAV应用的程序。我们能调用导入相同的WAV文件到不同的源，
//'phaser.wav' 的缓冲区建立了一次，'gPhaser1' and 'gPhaser2' 用于背景音乐的缓冲区。
//不用处理缓冲区因为系统会自动处理。

void KillALData()
{
	// 释放所有的缓冲区数据.
	for (vector<ALuint>::iterator iter = Buffers.begin(); iter != Buffers.end(); ++iter)
    alDeleteBuffers(1, iter);
    
	// 释放所有的源数据.
	for (vector<ALuint>::iterator iter = Sources.begin(); iter != Sources.end(); ++iter)
    alDeleteBuffers(1, iter);
    
	// 清除列表.
	Buffers.clear();
	Sources.clear();
}
//我们已完成了前述的工作。然后就是释放他们。
try
{
	InitOpenAL();
    
	LoadALData();
}
catch(string err)
{
	cout << "OpenAL error: " << err.c_str() << endl;
}
//如果导入源时出错，我们将改正他。这将借助程序返回的报告。
/*
 That's it. A more advanced way of reporting errors, and a more robust way of loading 
 your wav files. We may find we need to do some modifications in the future to allow 
 for more flexibility, but for now we will be using this source for basic file loading 
 in future tutorials. Expect future tutorials to expand on this code.
 
 See the Java Bindings for OpenAL page for the Java version of this tutorial (adapted 
 by: Athomas Goldberg)
 */