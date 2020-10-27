<template>
  <div class="home">
    <UrlFinder/>
  </div>
</template>

<script>
// @ is an alias to /src
import UrlFinder from '@/components/UrlFinder.vue'

export default {
  name: 'Home',
  components: {
    UrlFinder
  }
}
</script>
