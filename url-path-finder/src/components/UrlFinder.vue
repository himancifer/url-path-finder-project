<template>
  <v-container>
      <v-row justify="space-around">
      <v-card width="1400">
      
       <v-card-text>
          <v-row>
            <v-col cols = "5">
              <v-text-field label="Source URL" placeholder="https://example.com/" outlined v-model="src"></v-text-field>
            </v-col>  
            <v-col cols = "5">
              <v-text-field label="Destination URL" placeholder="http://www.icann.org/topics/idn/" outlined v-model="dest"></v-text-field>
            </v-col>  
            <v-col cols = "2">
              <v-btn
                class="mx-2" fab dark color="indigo" v-on:click="findPaths">
                <v-icon dark>
                  mdi-arrow-right-bold-circle
                </v-icon>
              </v-btn>
            </v-col>  
          </v-row>
        </v-card-text>
        
        <v-card-text v-if="paths.length">
          <div class="font-weight-bold ml-8 mb-2">
            PATH
          </div>

          <v-timeline
            align-top
            dense
          >
            <v-timeline-item
              v-for="path in paths"
              :key="path"
              :color="randomColor()"
              small
            >
              <div>
                <div class="font-weight-normal">
                  <a :href="path"><strong>{{ path }}</strong></a>
                </div>
              </div>
            </v-timeline-item>
          </v-timeline>
        </v-card-text>

        <v-card-text>
          <v-btn class="ma-2" outlined color="indigo" v-on:click="clearInputs()">
            Clear
          </v-btn>
          <v-btn class="ma-2" outlined color="indigo" v-on:click="showLayers = true" v-if ="layers.length">
            Show All Layers
          </v-btn>
        </v-card-text>
      </v-card>
      <v-card width="1400" v-if="showLayers">
        <v-card-text  v-for="layer in layers" :key="layer">
          <div class="font-weight-bold ml-8 mb-2">
            <p> Layer Number : {{ idx++ }}</p>
          </div>

          <v-timeline
            align-top
            dense
          >
            <v-timeline-item
              v-for="path in layer"
              :key="path"
              :color="randomColor()"
              small
            >
              <div>
                <div class="font-weight-normal">
                  <a :href="path"><strong>{{ path }}</strong></a>
                </div>
              </div>
            </v-timeline-item>
          </v-timeline>
        </v-card-text>

        <v-card-text>
          <v-btn class="ma-2" outlined color="indigo" v-on:click="showLayers = false">
            Close
          </v-btn>
        </v-card-text>
      </v-card>
    </v-row>
  </v-container>
</template>


<script>
import axios from 'axios';
  export default {
    name: 'UrlFinder',

    data: () => ({
      src : "",
      dest : "",
      paths: [],
      layers : [],
      color : "red",
      showLayers : false,
      idx : 1
    }),

    methods: {
      randomColor(){
          return this.$randomColor();
      },

      async findPaths(){
        if(this.src == "" || this.dest == ""){
          alert("No Inputs");
          return;
        }
        let response = await axios.post("http://localhost:3000/api/find-path",{src : this.src,dest : this.dest,maxHops:3});
        this.paths = response.data.paths;
        this.layers = response.data.layers;
        console.log(this.layers);
      },

      clearInputs(){
        this.src = "",
        this.dest = "",
        this.paths = [],
        this.showLayers = false
        this.idx = 1,
        this.layers = []
      },
    },  
}
</script>
