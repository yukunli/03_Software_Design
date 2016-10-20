
def get_data(line): # this function is to translate 6 bytes to 3 WORD data 
        try:
                
##                sample1_low=int(str(line[0]),0)
                sample1_low =ord(line[0])
                sample1_high=ord(line[1])
                sample1Value = sample1_high*256 + sample1_low
                if(sample1_high>=128):
                    sample1Value=sample1Value-65536

                sample2_low=ord(line[2])
                sample2_high=ord(line[3])
                sample2Value = sample2_high*256 + sample2_low
                if(sample2_high>=128):
                    sample2Value=sample2Value-65536

                sample3_low=ord(line[4])
                sample3_high=ord(line[5])
                sample3Value = sample3_high*256 + sample3_low
                if(sample3_high>=128):
                    sample3Value=sample3Value-65536
                    

                return float(sample1Value)/1000,float(sample2Value)/1000,float(sample3Value)/1000
        except:
                return(0,0,0)
    
