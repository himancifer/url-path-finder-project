<template>
  <v-app>
    <v-app-bar
      app
      color="primary"
      dark
    >
    URL Path Finder
    </v-app-bar>
      
  
    <v-main>
      <UrlFinder></UrlFinder>
    </v-main>
  </v-app>
</template>

<script>

import UrlFinder from "./components/UrlFinder"
export default {
  name: 'App',

  components: {
     UrlFinder
  },

  data: () => ({
    //
  }),
};
</script>
