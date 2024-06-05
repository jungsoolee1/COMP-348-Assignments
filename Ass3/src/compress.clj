(ns compress
  (:require [clojure.string :as str]))


(defn getFrequencies
  []
  (let [file-content (slurp "frequency.txt") 
        words (str/split file-content #" ")
        listWords (distinct words)] 
    (into [] listWords)))

(def frequency (getFrequencies))

(defn replaceWithIndex
  [words frequencies]
  (map #(if-let [index (.indexOf frequencies (str/lower-case %))]
          (if (= index -1) 
            %
            index)
          %) 
       words))

(defn replaceWithWords
  [words frequencies]
  (map #(if (try
              (Integer/parseInt %)
              true
              (catch NumberFormatException e
                false))
          (get frequencies (Integer/parseInt %))
          %)
       words))

(defn transformString
  [stringConvert]
  (str/replace (str/replace stringConvert #"([,\.\?\!\(\)\[\]\@\$])" " $1 ") #"(\d+)" "@$1@"))

(defn transformDecompress
  [outputSentence] 
  (str/replace (str/replace (str/replace (str/replace (str/replace (apply str (interpose " " outputSentence)) #"\s*([,\.\?\!\)\]])\s*" "$1 ") #"\@(\d+)\@" "$1") #"\s*([\(\[\@\$])\s*" " $1") #"([\)\]])\s*([,\.\?\!])" "$1$2") #"([\.\?\!])\s(\w)" (str "$1 " (str/upper-case "$2"))))

(defn compressFile
  [file-name]
  (let [inputString (transformString (slurp file-name))
        words (str/split inputString #"\s+")
        wordsVector (into [] words)
        outputList (replaceWithIndex wordsVector frequency)
        outputFile (str file-name ".ct")]
    (spit outputFile (apply str (interpose " " outputList)))))

(defn decompressFile
  [file-name]
  (println "")
  (let [inputString (slurp file-name)
        words (str/split inputString #"\s+")
        wordsVector (into [] words)
        outputSentence (replaceWithWords wordsVector frequency)
        outputString (transformDecompress outputSentence)
        realSentence (str (str/upper-case (subs outputString 0 1)) (subs outputString 1))]
    (println realSentence)))