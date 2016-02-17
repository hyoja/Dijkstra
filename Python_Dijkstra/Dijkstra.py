from pip._vendor.distlib.compat import raw_input
class InputFileReader:
    fileName = ''
    filePointer = ''
    def __init__(self):
        isReaded = 0
        while isReaded == 0 :
            print("type your file name : input.txt")
            self.fileName = raw_input()
            try :
                self.filePointer = open(self.fileName, 'r+')
                isReaded = 1
            except :
                isReaded = 0
        self.filePointer = open(self.fileName, 'r+')
    def ReadLine(self):
        tempReadedFileString = self.filePointer.readline()
        print(tempReadedFileString)
    def GetSplitedLine(self):
        splitedString = self.filePointer.readline()
        if splitedString == '':
            self.filePointer.close()
            return ''
        else :
            return  splitedString.split()
            
    def InitializeFilePointer(self):
        self.filePointer = open(self.fileName, 'r+')
        

class MainProgram:
    inputFileReader = ''
    nodeDictionary = {}
    uniqueNodeCounter = 0
    matrix = []
    
    def __init__(self):
        self.inputFileReader = InputFileReader()
    def MakeAdjacencyMatrix(self):
        while True:
            splitedString = self.inputFileReader.GetSplitedLine()
            if splitedString == '' :
                break
            for i in range(0, len(splitedString)) :
                if splitedString[i].isdigit() :
                    continue
                if splitedString[i].isalpha(): 
                    if (splitedString[i] in self.nodeDictionary) == False :
                        self.nodeDictionary[splitedString[i]] = self.uniqueNodeCounter
                        self.uniqueNodeCounter += 1
        
        self.matrix = [[0 for col in range(self.uniqueNodeCounter)] for row in range(self.uniqueNodeCounter)]
        for x in range(self.uniqueNodeCounter) :
            for y in range(self.uniqueNodeCounter) :
                if(x == y) :
                    self.matrix[x][y] = 0
                else :
                    self.matrix[x][y] = 9999   
                     
        self.inputFileReader.InitializeFilePointer()
        xIndexOfMatrix = -1;
        yIndexOfMatrix = -1;
        while True:
            splitedString = self.inputFileReader.GetSplitedLine()
            if splitedString == '' :
                break
            for i in range(0, len(splitedString)) :
                if splitedString[i].isdigit() :
                    self.matrix[xIndexOfMatrix][yIndexOfMatrix] = splitedString[i]
                    self.matrix[yIndexOfMatrix][xIndexOfMatrix] = splitedString[i]
                    xIndexOfMatrix = -1;
                    yIndexOfMatrix = -1;
                if splitedString[i].isalpha():  
                    if(xIndexOfMatrix != -1) :
                        yIndexOfMatrix = self.nodeDictionary.get(splitedString[i])
                    else :
                        xIndexOfMatrix = self.nodeDictionary.get(splitedString[i])
        
    def PrintMatrix(self):
        stackString = ''
        for x in range(self.uniqueNodeCounter) :
            for y in range(self.uniqueNodeCounter) :
                stackString += str(self.matrix[x][y]) + "\t"
            stackString = ''
    
    def UsingDijkstraAlgorism(self):
        isReaded = 0
        IndexOfShortestPath = 0
        while isReaded == 0 :
            print("type your start node Name : (example) A")
            try :
                IndexOfShortestPath = int (self.nodeDictionary[str(raw_input())])
                isReaded = 1
            except :
                isReaded = 0
                
        startNodeIndex = IndexOfShortestPath
        
        isVisited = [0 for col in range(self.uniqueNodeCounter)]
        shortestPathWeightValue = [0 for col in range(self.uniqueNodeCounter)]
        pathList = [0 for col in range(self.uniqueNodeCounter)]
        
        for x in range(self.uniqueNodeCounter) :
            isVisited[x] = False
            shortestPathWeightValue[x] = 9999
        
        shortestPathWeightValue[IndexOfShortestPath] = 0
        for y in range(self.uniqueNodeCounter) :
            mostSmallValue = 9999
            for x in range(self.uniqueNodeCounter) :
                if isVisited[x] == False and mostSmallValue > shortestPathWeightValue[x] :
                    IndexOfShortestPath = x
                    mostSmallValue = shortestPathWeightValue[x]
                    
            isVisited[IndexOfShortestPath] = True
            
            for x in range(self.uniqueNodeCounter) :
                if(isVisited[x] == False and shortestPathWeightValue[x] > (int(self.matrix[x][IndexOfShortestPath]) + int(shortestPathWeightValue[IndexOfShortestPath]))) :
                    shortestPathWeightValue[x] = (int(self.matrix[x][IndexOfShortestPath]) + int(shortestPathWeightValue[IndexOfShortestPath]))
                    pathList[x] = IndexOfShortestPath;
                    
        pathString = ''
        
        IndexOfShortestPath = 0
        x = 0
        while isReaded == 0 :
            print("type your End node Name : (example) G")
            try :
                x = int (self.nodeDictionary[str(raw_input())])
                isReaded = 1
            except :
                isReaded = 0
        
        while True :
            if pathString == '' : 
                pathString = "("+str(self.matrix[int(pathList[x])][x]) +") -> "+list(self.nodeDictionary.keys())[list(self.nodeDictionary.values()).index(x)] + pathString
            else : 
                if int(pathList[x]) == 0:
                    if(startNodeIndex != 0) :
                        pathString = list(self.nodeDictionary.keys())[list(self.nodeDictionary.values()).index(x)] + " -> " + pathString
                    else :
                        pathString = "A -> "+"("+str(self.matrix[int(pathList[x])][x]) +") -> "+list(self.nodeDictionary.keys())[list(self.nodeDictionary.values()).index(x)] + " -> " + pathString
                    break
                else :
                    pathString = "("+str(self.matrix[int(pathList[x])][x]) +") -> "+list(self.nodeDictionary.keys())[list(self.nodeDictionary.values()).index(x)] + " -> " + pathString
            x = int(pathList[x])
        print(pathString +" / " + str(shortestPathWeightValue[x]))
        
program = MainProgram()
program.MakeAdjacencyMatrix()
program.UsingDijkstraAlgorism()
