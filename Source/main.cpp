#include <iostream>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <AudioFile.h>

#include <dsp/ImpulseResponse.h>

int main(int argc, char *args[])
{
    if(argc < 3)
	{
		std::cout<<"Please provide args: "<<args[0]<<" "<<"[Sample WAV file] [ir-file1]"<<std::endl;
		return 1;
	}

	std::cout<<"Processing..."<<std::endl;

	int blocksize = 2048;

	try {
		//Load example audio
		const std::string inputFilePath(args[1]); 
		AudioFile<double> a;
		a.load (inputFilePath);

		std::filesystem::path path = args[2];
		std::unique_ptr<dsp::ImpulseResponse> ir = std::make_unique<dsp::ImpulseResponse>(path.string().c_str(), a.getSampleRate());
		//wavState = mStagedIR->GetWavState();
		
		//Process example audio with NAM model
		double *readPointer = &a.samples[0][0];
		double *writePointer = &a.samples[0][0];
		int numSamples = a.getNumSamplesPerChannel();
		
		while(numSamples > 0)
		{
			int currentNumSamples = std::min(numSamples, blocksize);
			double** irPointers = ir->Process(&readPointer, 1, currentNumSamples);
			
			for(auto s = 0; s < currentNumSamples; s++)
				writePointer[s] = irPointers[0][s];

			readPointer += currentNumSamples;
			writePointer += currentNumSamples;
			numSamples -= currentNumSamples;

			int percent = (a.getNumSamplesPerChannel() - numSamples) * 100 / a.getNumSamplesPerChannel();
			std::cout<<"\r"<<percent<<" % "<<std::flush;
		}
		
		std::string outputFilePath;
		outputFilePath = "out.wav";
		a.save (outputFilePath, AudioFileFormat::Wave);
	}
	catch(const std::runtime_error &e)
	{
		std::cout<<"Runtime error: "<<e.what()<<std::endl;
	}

	std::cout<<"\rFinished"<<std::endl;
}
